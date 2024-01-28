/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:23:10 by hsirenko          #+#    #+#             */
/*   Updated: 2024/01/23 17:00:00 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_timecode timecode)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
		error("Wasn't able to fetch time");
	if (timecode == SECONDS)
		return (current_time.tv_sec + (current_time.tv_usec / 1e6));
	else if (timecode == MILLISECONDS)
		return ((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3));
	else if (timecode == MICROSECONDS)
		return ((current_time.tv_sec * 1e6) + current_time.tv_usec);
	else
		error("Wrong input. I expect SECONDS or MILLISECONDS, or MICROSECONDS");
	return (9999);
}

/*
 * HYBRID approach
 * given usleep is not precise
 * i usleep for majority of time ,
 * then refine wiht busy wait
*/
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < usec)
	{
		if (sim_finished(table))
			break ;
		elapsed = get_time(MICROSECONDS) - start;
		rem = usec - elapsed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (get_time(MICROSECONDS) - start < usec)
				;
	}
}

void	error(const char *error)
{
	printf(RED"%s"RST"\n", error);
	exit(EXIT_FAILURE);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->philo_n)
	{
		philo = table->philos + i;
		mtx_handler(&philo->philo_mtx, DESTROY);
		i++;
	}
	mtx_handler(&table->table_mtx, DESTROY);
	mtx_handler(&table->write_status_mtx, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECONDS) - philo->table->sim_start;
	if (get_bool(&philo->philo_mtx, &philo->full))
		return ;
	mtx_handler(&philo->table->write_status_mtx, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !sim_finished(philo->table))
		printf(YELLOW"%-6ld"RST" %d has taken a fork\n",
			elapsed, philo->id);
	else if (status == EATING && !sim_finished(philo->table))
		printf(YELLOW"%-6ld"MAGENTA" %d is eating"RST"\n",
			elapsed, philo->id);
	else if (status == THINKING && !sim_finished(philo->table))
		printf(YELLOW"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
	else if (status == SLEEPING && !sim_finished(philo->table))
		printf(YELLOW"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
	else if (status == DIED)
		printf(YELLOW"%-6ld"RST" %d died\n", elapsed, philo->id);
	mtx_handler(&philo->table->write_status_mtx, UNLOCK);
}

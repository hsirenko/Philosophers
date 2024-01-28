/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 05:08:22 by hsirenko          #+#    #+#             */
/*   Updated: 2024/01/23 17:27:26 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECONDS));
	increase_long(&philo->table->table_mtx,
		&philo->table->philos_functioning_num);
	write_status(TAKE_FIRST_FORK, philo);
	while (! sim_finished (philo->table))
		usleep(300);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	mtx_handler(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mtx_handler(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECONDS));
	philo->n_meals++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->n_meals == philo->table->meals_limit
		&& philo->table->meals_limit > 0)
		set_bool(&philo->philo_mtx, &philo->full, true);
	mtx_handler(&philo->first_fork->fork, UNLOCK);
	mtx_handler(&philo->second_fork->fork, UNLOCK);
}

void	think(t_philo *philo, bool pre_sim)
{
	long	t_think;

	if (!pre_sim)
		write_status(THINKING, philo);
	if (philo->table->philo_n % 2 == 0)
		return ;
	t_think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.21, philo->table);
}

static void	*dinner_sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECONDS));
	increase_long(&philo->table->table_mtx,
		&philo->table->philos_functioning_num);
	making_system_fair(philo);
	while (!sim_finished(philo->table))
	{
		if (get_bool(&philo->philo_mtx, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		think(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_limit == 0)
		return ;
	else if (table->philo_n == 1)
		thread_handler(&table->philos[0].thread_id,
			one_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_n)
			thread_handler(&table->philos[i].thread_id,
				dinner_sim, &table->philos[i], CREATE);
	}
	thread_handler(&table->watcher, watch_dinner, table, CREATE);
	table->sim_start = get_time(MILLISECONDS);
	set_bool(&table->table_mtx, &table->all_philos_ready, true);
	i = 0;
	while (i < table->philo_n)
	{
		thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&table->table_mtx, &table->sim_end, true);
	thread_handler(&table->watcher, NULL, NULL, JOIN);
}

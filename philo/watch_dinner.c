/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:53:04 by helensirenko      #+#    #+#             */
/*   Updated: 2024/01/24 01:14:35 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	time_to_die = philo->table->time_to_die / 1e3;
	elapsed = get_time(MILLISECONDS) - get_long(&philo->philo_mtx,
			&philo->last_meal_time);
	if (get_bool(&philo->philo_mtx, &philo->full))
		return (false);
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*watch_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_philos_function(&table->table_mtx,
			&table->philos_functioning_num, table->philo_n))
		;
	while (!sim_finished(table))
	{
		i = -1;
		while (++i < table->philo_n && !sim_finished(table) 
			&& !get_bool(&table->philos->philo_mtx, &table->philos->full))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mtx, &table->sim_end, true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}

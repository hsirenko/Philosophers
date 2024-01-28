/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 00:15:10 by hsirenko          #+#    #+#             */
/*   Updated: 2024/01/23 17:11:22 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//if odd -> first_left;
// if even -> first_right;
static void	fork_assign(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_n;

	philo_n = philo->table->philo_n;
	philo->first_fork = &forks[(pos + 1) % philo_n];
	philo->second_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_n];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_n)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->n_meals = 0;
		philo->table = table;
		mtx_handler(&philo->philo_mtx, INIT);
		fork_assign(philo, table->forks, i);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->sim_end = false;
	table->all_philos_ready = false;
	table->philos_functioning_num = 0;
	table->philos = malloc_handler(sizeof(t_philo) * table->philo_n);
	table->forks = malloc_handler(sizeof(t_fork) * table->philo_n);
	mtx_handler(&table->table_mtx, INIT);
	mtx_handler(&table->write_status_mtx, INIT);
	while (i < table->philo_n)
	{
		mtx_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
}

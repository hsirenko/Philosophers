/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronize_watch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:15:09 by hsirenko          #+#    #+#             */
/*   Updated: 2024/01/23 16:57:19 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//SPINLOCK to synchronize philo start
void	wait_all_philos(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_philos_ready))
		;
}

//monitor busy waits until all philos are not functioning
bool	all_philos_function(t_mtx *mtx, long *philos, long philo_n)
{
	bool	return1;

	return1 = false;
	mtx_handler(mtx, LOCK);
	if (philo_n == *philos)
		return1 = true;
	mtx_handler(mtx, UNLOCK);
	return (return1);
}

//increase all philos functioning to synchro with watcher
void	increase_long(t_mtx *mtx, long *philo_num)
{
	mtx_handler(mtx, LOCK);
	(*philo_num)++;
	mtx_handler(mtx, UNLOCK);
}

void	making_system_fair(t_philo *philo)
{
	if (philo->table->philo_n % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(6e4, philo->table);
	}
	else
	{
		if (philo-> id % 2)
			think(philo, true);
	}
}

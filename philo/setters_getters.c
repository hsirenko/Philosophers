/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:44:36 by hsirenko          #+#    #+#             */
/*   Updated: 2024/01/23 17:08:50 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(t_mtx *mtx, bool *val)
{
	bool	return1;

	mtx_handler(mtx, LOCK);
	return1 = *val;
	mtx_handler(mtx, UNLOCK);
	return (return1);
}

void	set_bool(t_mtx *mtx, bool *dst, bool val)
{
	mtx_handler(mtx, LOCK);
	*dst = val;
	mtx_handler(mtx, UNLOCK);
}

long	get_long(t_mtx *mtx, long *val)
{
	long	return1;

	mtx_handler(mtx, LOCK);
	return1 = *val;
	mtx_handler(mtx, UNLOCK);
	return (return1);
}

void	set_long(t_mtx *mtx, long *dst, long val)
{
	mtx_handler(mtx, LOCK);
	*dst = val;
	mtx_handler(mtx, UNLOCK);
}

bool	sim_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->sim_end));
}

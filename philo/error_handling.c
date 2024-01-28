/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 00:20:14 by hsirenko          #+#    #+#             */
/*   Updated: 2024/01/23 17:16:21 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*malloc_handler(size_t size)
{
	void	*return1;

	return1 = malloc(size);
	if (return1 == NULL)
		error("malloc error");
	return (return1);
}

static void	mtx_error_handler(int status, t_opscode opscode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opscode == LOCK || opscode == UNLOCK))
		error("The value specified by mutex is invalid.");
	else if (status == EINVAL && opscode == INIT)
		error("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error("A deadlock would occur if the thread blocked"
			"waiting for mutex.");
	else if (status == EPERM)
		error("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error("The process cannot allocate enough memory"
			"to create another mutex.");
	else if (status == EBUSY)
		error("Mutex is locked");
}

void	mtx_handler(t_mtx *mutex, t_opscode opscode)
{
	if (opscode == INIT)
		mtx_error_handler(pthread_mutex_init(mutex, NULL), opscode);
	else if (opscode == DESTROY)
		mtx_error_handler(pthread_mutex_destroy(mutex), opscode);
	else if (opscode == LOCK)
		mtx_error_handler(pthread_mutex_lock(mutex), opscode);
	else if (opscode == UNLOCK)
		mtx_error_handler(pthread_mutex_unlock(mutex), opscode);
	else
		error("Wrong opscode for mutex handle. "
			"I expect INIT, DESTROY, LOCK, or UNLOCK");
}

static void	pthread_error_handler(int status, t_opscode opscode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && opscode == CREATE)
		error("The value specified by attr is invalid.");
	else if (status == EPERM)
		error("The caller does not have appropriate permission to set the "
			"required scheduling parameters or scheduling policy.");
	else if (status == EINVAL && (opscode == DETACH || opscode == JOIN))
		error(" The implementation has detected"
			" that the value specified by thread does"
			" not refer to a joinable thread.");
	else if (status == ESRCH)
		error("No thread could be found corresponding "
			"to that specified by the given thread ID, thread.");
	else if (status == EAGAIN)
		error("No resources to create another thread");
	else if (status == EDEADLK)
		error("A deadlock was detected or the value "
			"of thread specifies the calling thread.");
}

void	thread_handler(pthread_t *thread, void *(*start_routine)(void *),
			void *arg, t_opscode opscode)
{
	if (opscode == CREATE)
		pthread_error_handler(pthread_create(thread, NULL,
				start_routine, arg), opscode);
	else if (opscode == DETACH)
		pthread_error_handler(pthread_detach(*thread), opscode);
	else if (opscode == JOIN)
		pthread_error_handler(pthread_join(*thread, NULL), opscode);
	else
		error("Wrong opscode for mutex handle. "
			"I expect CREATE, DETACH, or JOIN");
}

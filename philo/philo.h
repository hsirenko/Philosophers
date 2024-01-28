/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:43:04 by hsirenko          #+#    #+#             */
/*   Updated: 2024/01/23 16:50:25 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <errno.h>

// ANSI Escape Sequences for Bold Text Colors
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN    "\033[1;36m"
# define WHITE   "\033[1;37m"
# define RST        "\033[0m"

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# ifndef PHILOS_LIMIT
#  define PHILOS_LIMIT 200
# endif

typedef enum e_opscode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	DETACH,
	JOIN,
}	t_opscode;

typedef enum e_timecode
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}	t_timecode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
}	t_status;

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;

}	t_fork;

typedef struct s_philo
{
	int			id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mtx		philo_mtx;
	long		n_meals;
	bool		full;
	long		last_meal_time;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	t_philo		*philos;
	t_fork		*forks;
	t_mtx		table_mtx;
	t_mtx		write_status_mtx;
	pthread_t	watcher;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		philo_n;
	long		sim_start;
	bool		sim_end;
	bool		all_philos_ready;
	long		meals_limit;
	long		philos_functioning_num;
}	t_table;

//utils
void	error(const char *error);
long	get_time(t_timecode timecode);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
void	write_status(t_status status, t_philo *philo);

void	input_check(t_table *table, char **argv);

void	*malloc_handler(size_t size);
void	mtx_handler(t_mtx *mutex, t_opscode opscode);
void	thread_handler(pthread_t *thread, void *(*start_routine)(void *),
			void *arg, t_opscode opscode);
void	data_init(t_table *table);

void	data_init(t_table *table);
//getters&setters
bool	get_bool(t_mtx *mtx, bool *val);
void	set_bool(t_mtx *mtx, bool *dst, bool val);
long	get_long(t_mtx *mtx, long *val);
void	set_long(t_mtx *mtx, long *dst, long val);
bool	sim_finished(t_table *table);

//synchronize & watch
void	wait_all_philos(t_table *table);
bool	all_philos_function(t_mtx *mtx, long *philos, long philo_n);
void	increase_long(t_mtx *mtx, long *philo_num);
void	making_system_fair(t_philo *philo);

//dinner simulation
void	dinner_start(t_table *table);
void	think(t_philo *philo, bool pre_sim);
//watcher
void	*watch_dinner(void *data);

#endif

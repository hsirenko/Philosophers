/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:01:06 by helensirenko      #+#    #+#             */
/*   Updated: 2024/01/23 17:07:43 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*nb;
	int			i;

	len = 0;
	i = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error("Wrong input. Please provide only positive numbers");
	while (str[i])
	{
		if (!is_digit(str[i]))
			error("Wrong input. Please enter only valid digits from 0 to 9");
		else 
			i++;
	}
	nb = str;
	while (is_digit(*str++))
		str++;
	if (len > 10)
		error("Too big number. The input should not exceed INT_MAX");
	return (nb);
}

static long	ft_atol(const char *str)
{
	long	nb;

	nb = 0;
	str = valid_input(str);
	while (is_digit(*str))
		nb = nb * 10 + *str++ - '0';
	if (nb > INT_MAX)
		error("Wrong input. Please provide only positive numbers");
	return (nb);
}

void	input_check(t_table *table, char **argv)
{
	table->philo_n = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error("Use time stamps greater than 60 milliseconds.");
	if (argv[5])
		table->meals_limit = ft_atol(argv[5]);
	else
		table->meals_limit = -1;
}

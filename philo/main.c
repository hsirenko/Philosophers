/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:19:11 by hsirenko          #+#    #+#             */
/*   Updated: 2024/01/23 16:58:31 by helensirenko     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		input_check(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error("Invalid input\n"
			GREEN"Correct input is: ./philo 5 600 200 200 [5]\n"RST);
	}
}

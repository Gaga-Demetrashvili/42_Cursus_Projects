/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:18:13 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/03 12:17:13 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		parse_input(&data, av);
		data_init(&data);
		dinner_start(&data);
	}
	else
		error_exit("Please enter correct amount of args.");
	return (EXIT_SUCCESS);
}

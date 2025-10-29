/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:01:29 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/29 23:54:33 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_args
{
	NUM_OF_PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUM_OF_TIMES_EACH_PHILO_MUST_EAT
}		t_args;

void	args_validation(int ac, char **argv, int **args, int num_of_args);
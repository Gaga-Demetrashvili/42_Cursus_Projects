/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:18:13 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/30 16:18:43 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	num_of_args;
	int	args[5];
	int	val_and_init_res;

	num_of_args = 5;
	memset(args, 0, sizeof(args));
	val_and_init_res = 0;
	val_and_init_res = args_validation_and_initialization(ac, av, args,
			num_of_args);
	if (val_and_init_res)
		return (val_and_init_res);
	return (0);
}

// #define THREAD_NUM 9

// char	**global_av;

// void	*task(void *arg)
// {
// 	int	i;

// 	i = *(int *)arg;
// 	printf("Thread %d working\n", i);
// 	usleep(500000); // 500 000 microseconds = 0.5 secs
// 	printf("Thread %d | string to convert \"%s\" | atoi res - %d\n", i,
// 		global_av[i + 1], ft_atoi(global_av[i + 1]));
// 	printf("End of threads\n");
// 	return (arg);
// }

// int	main(int ac, char **av)
// {
// 	int i = 0;
// 	pthread_t th[THREAD_NUM];

// 	global_av = av;

// 	while (i < THREAD_NUM)
// 	{
// 		int *a = malloc(sizeof(int));
// 		*a = i;
// 		if (pthread_create(&th[i], NULL, &task, (void *)a) != 0)
// 		{
// 			printf("Error while creating a thread\n");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < THREAD_NUM)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 		{
// 			printf("Error while joining a thread\n");
// 			return (2);
// 		}
// 		i++;
// 	}

// 	return (0);
// }
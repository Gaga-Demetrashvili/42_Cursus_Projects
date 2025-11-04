/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:56:51 by gaga              #+#    #+#             */
/*   Updated: 2025/11/04 22:40:07 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with the malloc");
	return (ret);
}

static void	handle_semaphore_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (WAIT == opcode || DESTROY == opcode
			|| POST == opcode))
		error_exit("sem is not a valid semaphore.");
	else if (EINVAL == status && INIT == opcode)
		error_exit("value exceeds SEM_VALUE_MAX.");
	else if (EOVERFLOW == status)
		error_exit("Maximum allowable value for semaphore would be exceeded.");
	else if (ENOSYS == status)
		error_exit("System does not support process-shared semaphores");
	else if (EAGAIN == status)
		error_exit("The  operation  could  not be performed without blocking");
	else if (EINTR == status)
		error_exit("The call was interrupted by a signal handler");
	else if (ETIMEDOUT == status)
		error_exit("The call timed out before the semaphore  could be locked.");
}

void	safe_semaphore_handle(sem_t *semaphore, t_opcode opcode,
		unsigned int value)
{
	if (INIT == opcode)
		handle_semaphore_error(sem_init(semaphore, 0, value), opcode);
	else if (DESTROY == opcode)
		handle_semaphore_error(sem_destroy(semaphore), opcode);
	else if (WAIT == opcode)
		handle_semaphore_error(sem_wait(semaphore), opcode);
	else if (POST == opcode)
		handle_semaphore_error(sem_post(semaphore), opcode);
	else
		error_exit("Wrong opcode for semaphore handle");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread is not joinable");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that "
					"specified by the given thread ID");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of "
					"thread specifies the calling thread");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle: "
					"use <CREATE> <JOIN> <DETACH>");
}

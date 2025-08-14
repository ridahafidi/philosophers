/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:32:34 by marvin            #+#    #+#             */
/*   Updated: 2025/08/14 18:20:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void status_err(int status)
{
    if (status == EAGAIN)
        ft_putstr_fd("Resource temporarily unavailable\n", STDERR_FILENO);
    else if (status == EINVAL)
        ft_putstr_fd("Invalid argument\n", STDERR_FILENO);
    else if (status == EPERM)
        ft_putstr_fd("Operation not permitted\n", STDERR_FILENO);
    else if (status == ESRCH)
        ft_putstr_fd("No such thread\n", STDERR_FILENO);
    else if (status == EDEADLK)
        ft_putstr_fd("Deadlock detected\n", STDERR_FILENO);
    else
        ft_putstr_fd("Unknown error\n", STDERR_FILENO);
}

static void handle_err(int status, t_tpm tpm)
{
    if (status == 0)
        return;
    ft_putstr_fd("Error: ", STDERR_FILENO);
    if (tpm == CREATE)
        ft_putstr_fd("pthread_create failed: ", STDERR_FILENO);
    else if (tpm == JOIN)
        ft_putstr_fd("pthread_join failed: ", STDERR_FILENO);
    else if (tpm == DETACH)
        ft_putstr_fd("pthread_detach failed: ", STDERR_FILENO);
    status_err(status);
    exit(EXIT_FAILURE);
}

void    safe_handle_pthread(pthread_t *thread,void *arg, void *(routine)(void *), t_tpm tpm)
{
    if (tpm == CREATE)
        handle_err(pthread_create(thread, NULL, routine, arg), tpm);
    else if (tpm == JOIN)
        handle_err(pthread_join(*thread, NULL), tpm);
    else if (tpm == DETACH)
        handle_err(pthread_detach(*thread), tpm);
    else
    {
        ft_putstr_fd("wrong tpm given\n", STDERR_FILENO);
        exit (EXIT_FAILURE);
    }
}

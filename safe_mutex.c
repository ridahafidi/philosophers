/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:30:05 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/14 15:40:58 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void    status_err(int status)
{
    if (status == EAGAIN)
        ft_putstr_fd("Resource temporarily unavailable\n", STDERR_FILENO);
    else if (status == ENOMEM)
        ft_putstr_fd("Insufficient memory\n", STDERR_FILENO);
    else if (status == EPERM)
        ft_putstr_fd("Operation not permitted\n", STDERR_FILENO);
    else if (status == EBUSY)
        ft_putstr_fd("Resource busy\n", STDERR_FILENO);
    else if (status == EINVAL)
        ft_putstr_fd("Invalid argument\n", STDERR_FILENO);
    else if (status == EDEADLK)
        ft_putstr_fd("Deadlock detected\n", STDERR_FILENO);
    else
        ft_putstr_fd("Unknown error\n", STDERR_FILENO);
}

static void    handle_err(int status, t_opm opm)
{
    if (status == 0)
        return; // Success
    ft_putstr_fd("Error: ", STDERR_FILENO);
    if (opm == INIT)
        ft_putstr_fd("pthread_mutex_init failed: ", STDERR_FILENO);
    else if (opm == LOCK)
        ft_putstr_fd("pthread_mutex_lock failed: ", STDERR_FILENO);
    else if (opm == UNLOCK)
        ft_putstr_fd("pthread_mutex_unlock failed: ", STDERR_FILENO);
    else if (opm == DESTROY)
        ft_putstr_fd("pthread_mutex_destroy failed: ", STDERR_FILENO);
    status_err(status);
    exit(EXIT_FAILURE);
}

void    safe_handle_mutex(pthread_mutex_t *mtx, t_opm opm)
{
    if (opm == INIT)
        handle_err(pthread_mutex_init(mtx, NULL), opm);
    else if (opm == LOCK)
        handle_err(pthread_mutex_lock(mtx), opm);
    else if (opm == UNLOCK)
        handle_err(pthread_mutex_unlock(mtx), opm);
    else if (opm == DESTROY)
        handle_err(pthread_mutex_destroy(mtx), opm);
    else
    {
        ft_putstr_fd("wrong opm given\n", STDERR_FILENO);
        exit (EXIT_FAILURE);
    }
}
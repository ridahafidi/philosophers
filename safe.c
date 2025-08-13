/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:30:05 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/13 02:55:01 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *safe_malloc(size_t n_bytes)
{
    void *ret;

    ret = malloc(n_bytes);
    if (!ret)
    {
        ft_putstr_fd("malloc failed \n", 2);
        exit(EXIT_FAILURE); 
    }
    return (ret);
}

void    handle_err(int status, t_opm opm)
{
    
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
        ft_putstr_fd("wrong opm given\n", 2);
        exit (EXIT_FAILURE);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:40:53 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/14 15:41:37 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *safe_malloc(size_t n_bytes)
{
    void *ret;

    ret = malloc(n_bytes);
    if (!ret)
    {
        ft_putstr_fd("malloc failed \n", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    return (ret);
}

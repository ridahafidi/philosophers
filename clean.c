/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:14:30 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/14 22:42:33 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    clean_data(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        safe_handle_mutex(&data->philos[i].lm, DESTROY);
        safe_handle_mutex(&data->philos[i].me, DESTROY);
        safe_handle_mutex(&data->forks[i].fork, DESTROY);
        i++;
    }
    safe_handle_mutex(&data->stop_mutex, DESTROY);
    safe_handle_mutex(&data->print_mutex, UNLOCK);
    safe_handle_mutex(&data->print_mutex, DESTROY);
    free(data->philos);
    free(data->forks);
}

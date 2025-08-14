/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:24:36 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/14 21:12:54 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_last_meal(t_philo *philo)
{
    long last_meal;
    safe_handle_mutex(&philo->lm, LOCK);
    last_meal = philo->last_meal;
    safe_handle_mutex(&philo->lm, UNLOCK);
    return (last_meal);
}

int check_stop(t_data *data)
{
    safe_handle_mutex(&data->stop_mutex, LOCK);
    if (!data->stop)
    {
        safe_handle_mutex(&data->stop_mutex, UNLOCK);    
        return (0);
    }
    else
    {
        safe_handle_mutex(&data->stop_mutex, UNLOCK);
        return (1);
    }
}

void    set_stop(t_data *data)
{
    safe_handle_mutex(&data->stop_mutex, LOCK);
    data->stop = 1;
    safe_handle_mutex(&data->stop_mutex, UNLOCK);
}

int check_meals_eaten(t_data *data, t_philo *philo)
{
    safe_handle_mutex(&philo->me, LOCK);
    if (data->max_meals > 0 && data->max_meals <= philo->meals_eaten) ///
    {
        safe_handle_mutex(&philo->me, UNLOCK);
        return (1);
    }
    else
        safe_handle_mutex(&philo->me, UNLOCK);
    return (0);
}

void    set_last_meal(t_philo *philo, int flag)
{
    safe_handle_mutex(&philo->lm, LOCK);
    if (flag == 0)
        philo->last_meal = philo->data->start_time_ms;
    else
        philo->last_meal = now_ms();
    safe_handle_mutex(&philo->lm, UNLOCK);
}

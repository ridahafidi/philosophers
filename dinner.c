/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:53:41 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/15 22:18:23 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    solo_case(t_data *data, int pos)
{
    state_print(data, TAKEN_FORK, &data->philos[pos]);
    smart_sleep(data->time_to_die, data);
    state_print(data, DEAD, &data->philos[pos]);
    set_stop(data);
}

void    *monitor(void *arg)
{
    t_data *data;
    int i;
    long last_meal;
    int all_done;

    data = (t_data *)arg;
    while(!check_stop(data))
    {
        i = 0;
        all_done = data->max_meals > 0;
        while (i < data->num_philos)
        {
            last_meal = get_last_meal(&data->philos[i]);
            if (death_check(last_meal, data->time_to_die))
            {
                set_stop(data);
                state_print(data, DEAD, &data->philos[i]);
                return (NULL);
            }
            // smart_sleep(1, data);
            if (!check_meals_eaten(data, &data->philos[i]))
                all_done = 0;
            i++;
        }
        if (all_done)
        {
            set_stop(data);
            return (NULL);
        }
    }
    return (NULL);
}
void    init_last_meal(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        set_last_meal(&data->philos[i], 0);
        i++;
    }
}

void    lunch_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        // if (i % 2 == 0)
        //     safe_handle_pthread(&data->philos[i].philo, &data->philos[i], routine, CREATE);
        // else
            safe_handle_pthread(&data->philos[i].philo, &data->philos[i], routine, CREATE);
        i++;
    }
}

void    wait_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        safe_handle_pthread(&data->philos[i].philo, NULL, NULL, JOIN);
        i++;
    }
}


void    dinner(t_data *data)
{
    int i;
    pthread_t   monitor_thread;

    i = 0;
    if (data->num_philos <= 0 || !data->max_meals)
    {
        set_stop(data);
        return ;
    }
    data->start_time_ms = now_ms();
    init_last_meal(data);
    if (data->num_philos == 1)
    {
        solo_case(data, 0);
        return ;
    }
    lunch_threads(data);
    safe_handle_pthread(&monitor_thread, data, monitor, CREATE);
    safe_handle_pthread(&monitor_thread, NULL, NULL, JOIN);
    wait_threads(data);
    set_stop(data);
}

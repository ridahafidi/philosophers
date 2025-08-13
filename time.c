/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:32:00 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/13 22:04:22 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    now_ms(void)
{
    struct timeval tv;
    long    now_ms;
    
    gettimeofday(&tv, NULL);
    now_ms = tv.tv_sec * 1e3 + tv.tv_usec / 1e3;
    return (now_ms);
}

long    timestamp(long start_time_ms)
{
    int ts;

    ts = now_ms() - start_time_ms;
    return (ts);
}

int death_check(long last_meal, long time_to_die)
{
    if ((now_ms() - last_meal) > time_to_die)
        return (1);
    return (0);
}

void    smart_sleep(long duration_ms, t_data *data)
{
    int     stopped;
    long    target;
    long    now;
    long    rem_us;
    long    chunk;

    if (duration_ms <= 0)
        return;
    target = now_ms() + duration_ms;
    while (1)
    {
        safe_handle_mutex(&data->stop_mutex, LOCK);
        stopped = data->stop;
        safe_handle_mutex(&data->stop_mutex, UNLOCK);
        if (stopped)
            return;
        now = now_ms();
        if (now >= target)
            return;
        rem_us = (target - now) * 1000L;
        if (rem_us > 1000L)
        {
            chunk = rem_us / 2;
            if (chunk > 5000L)
                chunk = 5000L;
            precise_usleep(chunk);
        }
        else
        {
            while (now_ms() < target) { /* busy-wait for <= 1 ms */ }
            return;
        }
    }
}

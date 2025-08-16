/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:49:42 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/16 22:51:06 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print_format(long ts, t_act act, int id)
{
	if (act == TAKEN_FORK)
		printf("%ld %d has taken a fork\n", ts, id);
	else if (act == EATING)
		printf("%ld %d is eating\n", ts, id);
	else if (act == SLEEPING)
		printf("%ld %d is sleeping\n", ts, id);
	else if (act == THINKING)
		printf("%ld %d is thinking\n", ts, id);
	else if (act == DEAD)
		printf("%ld %d died\n", ts, id);
}

void	state_print(t_data *data, t_act act, t_philo *philo)
{
	long	ts;
	int		stopped;

	ts = now_ms() - data->start_time_ms;
	safe_handle_mutex(&data->stop_mutex, LOCK);
	stopped = data->stop;
	safe_handle_mutex(&data->stop_mutex, UNLOCK);
	if (stopped && act != DEAD)
	{
		set_stop(data);
		return ;
	}
	safe_handle_mutex(&data->print_mutex, LOCK);
	print_format(ts, act, philo->id);
	safe_handle_mutex(&data->print_mutex, UNLOCK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:49:42 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/16 22:51:06 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	solo_case(t_data *data, int pos)
{
	state_print(data, TAKEN_FORK, &data->philos[pos]);
	smart_sleep(data->time_to_die, data);
	state_print(data, DEAD, &data->philos[pos]);
	set_stop(data);
}

void	*dead_handle(t_data *data, t_philo *philo)
{
	set_stop(data);
	state_print(data, DEAD, philo);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	long	last_meal;
	int		all_done;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		i = 0;
		all_done = data->max_meals > 0;
		while (i < data->num_philos)
		{
			last_meal = get_last_meal(&data->philos[i]);
			if (death_check(last_meal, data->time_to_die))
				return (dead_handle(data, &data->philos[i]));
			if (!check_meals_eaten(data, &data->philos[i]))
				all_done = 0;
			i++;
		}
		if (all_done)
		{
			return (set_stop(data), NULL);
		}
	}
	return (NULL);
}

void	dinner(t_data *data)
{
	pthread_t	monitor_thread;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:19:18 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/18 17:33:11 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_man(void)
{
	printf("Wrong usage !\n");
	printf("Usage : ./philo philos_number time_to_die ");
	printf("time_to_eat time_to_sleep\n");
	printf("all values should be greater than zero and reel numbers\n");
}

long	get_time_to_sleep(t_data *data, t_philo *philo)
{
	long	last_meal;

	last_meal = now_ms() - get_last_meal(philo);
	if (data->time_to_die < last_meal + data->time_to_sleep)
		return (data->time_to_die - last_meal);
	return (data->time_to_sleep);
}

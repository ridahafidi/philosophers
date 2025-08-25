/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:49:43 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/16 22:51:06 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	init_last_meal(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		set_last_meal(&data->philos[i], 0);
		i++;
	}
}

void	lunch_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		safe_handle_pthread(&data->philos[i].philo, &data->philos[i], routine,
			CREATE);
		i++;
	}
}

void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		safe_handle_pthread(&data->philos[i].philo, NULL, NULL, JOIN);
		i++;
	}
}

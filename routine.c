/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:49:43 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/16 22:51:06 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	take_fork(t_philo *philo, t_data *data)
{
	if (philo->id % 2 != 0)
	{
		safe_handle_mutex(&philo->left_fork->fork, LOCK);
		state_print(data, TAKEN_FORK, philo);
		if (check_stop(data))
		{
			safe_handle_mutex(&philo->left_fork->fork, UNLOCK);
			return (1);
		}
		safe_handle_mutex(&philo->right_fork->fork, LOCK);
		state_print(data, TAKEN_FORK, philo);
	}
	else
	{
		safe_handle_mutex(&philo->right_fork->fork, LOCK);
		state_print(data, TAKEN_FORK, philo);
		if (check_stop(data))
		{
			safe_handle_mutex(&philo->right_fork->fork, UNLOCK);
			return (1);
		}
		safe_handle_mutex(&philo->left_fork->fork, LOCK);
		state_print(data, TAKEN_FORK, philo);
	}
	return (0);
}

int	update_meals_eaten(t_philo *philo, t_data *data)
{
	safe_handle_mutex(&philo->me, LOCK);
	philo->meals_eaten++;
	if (data->max_meals > 0 && data->max_meals <= philo->meals_eaten)
	{
		safe_handle_mutex(&philo->me, UNLOCK);
		return (1);
	}
	safe_handle_mutex(&philo->me, UNLOCK);
	return (0);
}

int	eat(t_philo *philo, t_data *data)
{
	state_print(data, EATING, philo);
	set_last_meal(philo, 1);
	smart_sleep(data->time_to_eat, data);
	if (philo->id % 2 != 0)
	{
		safe_handle_mutex(&philo->left_fork->fork, UNLOCK);
		safe_handle_mutex(&philo->right_fork->fork, UNLOCK);
	}
	else
	{
		safe_handle_mutex(&philo->right_fork->fork, UNLOCK);
		safe_handle_mutex(&philo->left_fork->fork, UNLOCK);
	}
	return (update_meals_eaten(philo, data));
}

void	sleep_think(t_philo *philo, t_data *data)
{
	state_print(data, SLEEPING, philo);
	smart_sleep(data->time_to_sleep, data);
	state_print(data, THINKING, philo);
	if (data->num_philos % 2 != 0)
	{
		if (data->time_to_eat < data->time_to_sleep)
			smart_sleep(1, data);
		else
			smart_sleep(data->time_to_sleep, data);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!check_stop(data) && !check_meals_eaten(data, philo))
	{
		if (take_fork(philo, data))
			break ;
		if (eat(philo, data))
			break ;
		sleep_think(philo, data);
	}
	return (NULL);
}

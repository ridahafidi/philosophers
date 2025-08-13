/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:15:32 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/13 02:44:27 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        if (av[i][j] == '+')
            j++;
        else if (av[i][j] == '-')
            return (1);
        while(av[i][j])
        {
            if (!ft_isdigit(av[i][j]))
                return (1);
            j++;
        }
        if (!ft_atoi(av[i]))
            return (1);
        if (j > 10)
            return (1);
        i++;
    }
    return (0);
}

void    fill_data(char **av, t_data *data)
{
    data->num_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]) * 1e3;
    data->time_to_eat = ft_atoi(av[3]) * 1e3;
    data->time_to_sleep = ft_atoi(av[4]) * 1e3;
    if (!av[5])
        data->max_meals = -1;
    else
        data->max_meals = ft_atoi(av[5])
}

void    data_init(t_data *data)
{
    t_philo *philo;
    t_fork  *fork;
    int     i;

    data->end_simualtion = 0; // end flag
    philo = safe_malloc(sizeof(t_philo) * data->num_philos);
    fork = safe_malloc(sizeof(t_fork) * data->num_philos);
    i = 0;
    while (i <= data->num_philos)
    {
        safe_handle_mutex(&data->forks[i].fork, INIT);
        data->forks[i].fork_id = i + 1;
        i++;
    } 
}

int main(int ac, char **av)
{
    t_data data;

    if (ac == 5 ||  ac == 6)
    {
        if (check_args(av))
            return (EXIT_FAILURE);
        fill_data(av, &data); // fill table
        data_init(&data);
        return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}
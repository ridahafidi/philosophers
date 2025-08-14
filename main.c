/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:15:32 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/14 22:23:40 by rhafidi          ###   ########.fr       */
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
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (!av[5])
        data->max_meals = -1;
    else
        data->max_meals = ft_atoi(av[5]);
}

void    assign_forks(t_philo *philo, t_fork *forks, int pos)
{
    //if philo id odd id % 2 != 0
    // firs left
    // then right
    // else if even
    //first right
    // then left
    // deadlock free
    if (philo->id % 2)
    {
        philo->left_fork = &forks[(pos + 1) % philo->data->num_philos];
        philo->right_fork = &forks[pos];
    }
    else
    {
        philo->right_fork = &forks[pos];
        philo->left_fork = &forks[(pos + 1) % philo->data->num_philos];
    }   
}

void    philo_init(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i < data->num_philos)
    {
        philo = data->philos + i;
        philo->id = i + 1; // to start at index 1
        philo->data = data;
        philo->meals_eaten = 0;
        philo->last_meal = now_ms();
        assign_forks(philo, data->forks, i);
        safe_handle_mutex(&philo->lm, INIT);
        safe_handle_mutex(&philo->me, INIT);//lunch mutexes for  , lastmeal meals_eaten.
        i++;
    }
}
void    data_init(t_data *data)
{
    t_philo *philo;
    t_fork  *fork;
    int     i;

    data->stop = 0; // end flag
    data->start_time_ms = now_ms();
    data->philos = safe_malloc(sizeof(t_philo) * data->num_philos);
    data->forks = safe_malloc(sizeof(t_fork) * data->num_philos);
    i = 0;
    while (i < data->num_philos) // init forks
    {
        safe_handle_mutex(&data->forks[i].fork, INIT);
        data->forks[i].fork_id = i + 1;
        i++;
    }
    safe_handle_mutex(&data->print_mutex, INIT);
    safe_handle_mutex(&data->stop_mutex, INIT); // lunch mutexe for print
    philo_init(data);
}

int main(int ac, char **av)
{
    t_data data;

    if (ac == 5 ||  ac == 6)
    {
        if (check_args(av))
            return (EXIT_FAILURE);
        fill_data(av, &data); // fill table
        if (data.num_philos > 200)
        {
            ft_putstr_fd("bzaf", 2);
            return  (EXIT_FAILURE);
        }
        data_init(&data);// 3 180 60 60
        dinner(&data);
        clean_data(&data);
        return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:11:47 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/13 02:46:01 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "./libft/libft.h"

typedef struct s_fork
{
    pthread_mutex_t	fork;
    int             fork_id;
}           t_fork;

typedef struct s_data t_data;
typedef struct s_philo
{
	int				id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			last_meal;
	int				meals_eaten;
	pthread_t	philo;
    t_data      *data;
}	t_philo;

typedef struct s_data
{
    int				num_philos; // n philos
    int				time_to_die; // time stamp to die // quanta if a process exec timestamp
    int				time_to_eat; // 
    int				time_to_sleep;
    int				max_meals;
    int             start_simulation;
    int             end_simualtion; // 0 if 
    t_philo         *philos;
    t_fork          *forks;
}	t_data;

typedef enum s_opm
{
    INIT,
    LOCK,
    UNLOCK,
    DESTROY,
}           t_opm;

void    *safe_malloc(size_t n_bytes);

#endif
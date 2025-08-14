/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:11:47 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/14 22:23:23 by rhafidi          ###   ########.fr       */
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
#include <errno.h>

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
    pthread_mutex_t lm;
    pthread_mutex_t me;
	pthread_t	philo;
    t_data      *data;
}	t_philo;

typedef struct s_data
{
    int				num_philos; // n philos
    long			time_to_die; // time stamp to die // quanta if a process exec timestamp
    long			time_to_eat; // time the thread
    long			time_to_sleep;
    int				max_meals;
    long            start_time_ms;
    int             stop; // 0 if shouldnt stop 1 if should stop 
    t_philo         *philos;
    t_fork          *forks;
    pthread_mutex_t stop_mutex;
    pthread_mutex_t print_mutex;
}	t_data;

typedef enum s_opm
{
    INIT,
    LOCK,
    UNLOCK,
    DESTROY,
}           t_opm;

typedef enum s_tpm
{
    CREATE,
    JOIN,
    DETACH,
    
}           t_tpm;

typedef enum s_act
{
    TAKEN_FORK,
    EATING,
    SLEEPING,
    THINKING,
    DEAD,
}           t_act;

void    safe_handle_pthread(pthread_t *thread,void *arg, void *(*routine)(void *), t_tpm tpm);
void    *safe_malloc(size_t n_bytes);
void    safe_handle_mutex(pthread_mutex_t *mtx, t_opm opm);
long    now_ms(void);
long    timestamp(long start_time_ms);
void    smart_sleep(long duration_ms, t_data *data);
void    state_print(t_data *data, t_act act, t_philo *philo);
void    dinner(t_data *data);
int     death_check(long last_meal, long time_to_die);
long    get_last_meal(t_philo *philo);
int check_stop(t_data *data);
void    set_stop(t_data *data);
int check_meals_eaten(t_data *data, t_philo *philo);
void    *routine(void *arg);
void    set_last_meal(t_philo *philo, int flag);
void precise_usleep(long usec);
void    clean_data(t_data *data);

#endif
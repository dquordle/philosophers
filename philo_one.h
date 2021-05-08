#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_phil
{
	int	id;
	struct timeval start_time;
	struct timeval snack_time;
	pthread_mutex_t *right;
	pthread_mutex_t *left;
	int time_to_eat;
	int time_to_sleep;
	int number_to_eat;
	pthread_mutex_t *mut_chat;
}				t_phil;

typedef struct s_all
{
	pthread_mutex_t *mutex;
	pthread_t	*thread;
	t_phil **phil;
	struct timeval start_time;
	int		number_of_phil;
	int	time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_to_eat;
	pthread_mutex_t mut_chat;
}				t_all;


int	ft_atoi(const char *str);

#endif
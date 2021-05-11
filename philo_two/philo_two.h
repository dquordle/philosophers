#ifndef PHILO_TWO_H
#define PHILO_TWO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

typedef struct s_phil
{
	int	id;
	struct timeval start_time;
	struct timeval snack_time;
	int time_to_eat;
	int time_to_sleep;
	int number_to_eat;
	int full;
	sem_t *forks;
	sem_t *chat;
}				t_phil;

typedef struct s_all
{
	pthread_t	*thread;
	t_phil **phil;
	struct timeval start_time;
	int	number_of_phil;
	int	time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_to_eat;
	sem_t *forks;
	sem_t *chat;
}				t_all;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:16:31 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 13:16:32 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_eat(t_all *phil)
{
	struct timeval	time;

	sem_wait(phil->forks);
	gettimeofday(&time, 0);
	sem_wait(phil->chat);
	printf("%ld : philo #%d has taken a fork\n",
		get_time(time, phil->start_time), phil->id);
	sem_post(phil->chat);
	sem_wait(phil->forks);
	gettimeofday(&time, 0);
	sem_wait(phil->chat);
	phil->snack_time = time;
	printf("%ld : philo #%d has taken a fork\n",
		get_time(time, phil->start_time), phil->id);
	printf("%ld : philo #%d is eating\n",
		get_time(time, phil->start_time), phil->id);
	sem_post(phil->chat);
	my_usleep(phil->time_to_eat);
}

void	ft_sleep_n_chill(t_all *phil)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	sem_wait(phil->chat);
	printf("%ld : philo #%d is sleeping\n",
		   get_time(time, phil->start_time), phil->id);
	sem_post(phil->chat);
	sem_post(phil->forks);
	sem_post(phil->forks);
	my_usleep(phil->time_to_sleep);
	gettimeofday(&time, 0);
	sem_wait(phil->chat);
	printf("%ld : philo #%d is thinking\n",
		   get_time(time, phil->start_time), phil->id);
	sem_post(phil->chat);
}

void	ft_selfdestruction(t_all *phil)
{
	sem_wait(phil->plague);
	sem_post(phil->plague);
	exit(0);
}

void	*life(t_all *phil)
{
	int			eaten;
	pthread_t	thread_d;
	pthread_t	code_red;

	pthread_create(&thread_d, NULL, (void *)ft_check_death, phil);
	pthread_create(&code_red, NULL, (void *)ft_selfdestruction, phil);
	usleep(((phil->id - 1) % 2) * 200);
	eaten = 0;
	while (1)
	{
		ft_eat(phil);
		eaten++;
		if (phil->number_to_eat >= 0 && eaten >= phil->number_to_eat)
			sem_post(phil->full);
		ft_sleep_n_chill(phil);
	}
}

int	ft_sem_fail(t_all *all)
{
	if (all->forks == SEM_FAILED || all->chat == SEM_FAILED
		|| all->full == SEM_FAILED || all->plague == SEM_FAILED)
		return (1);
	return (0);
}

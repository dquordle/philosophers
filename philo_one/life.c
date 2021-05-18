/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:53:58 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 12:54:00 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_eat(t_phil *phil)
{
	struct timeval	time;

	pthread_mutex_lock(phil->left);
	gettimeofday(&time, 0);
	pthread_mutex_lock(phil->mut_chat);
	printf("%ld : philo #%d has taken a fork\n",
		get_time(time, phil->start_time), phil->id);
	pthread_mutex_unlock(phil->mut_chat);
	pthread_mutex_lock(phil->right);
	gettimeofday(&time, 0);
	pthread_mutex_lock(phil->mut_chat);
	phil->snack_time = time;
	printf("%ld : philo #%d has taken a fork\n",
		get_time(time, phil->start_time), phil->id);
	printf("%ld : philo #%d is eating\n",
		get_time(time, phil->start_time), phil->id);
	pthread_mutex_unlock(phil->mut_chat);
	my_usleep(phil->time_to_eat);
}

void	*life(t_phil *phil)
{
	struct timeval	time;
	int				eaten;

	usleep(((phil->id - 1) % 2) * 200);
	eaten = 0;
	while (1)
	{
		ft_eat(phil);
		eaten++;
		if (phil->number_to_eat >= 0 && eaten >= phil->number_to_eat)
			phil->full = 1;
		gettimeofday(&time, 0);
		pthread_mutex_lock(phil->mut_chat);
		printf("%ld : philo #%d is sleeping\n",
			get_time(time, phil->start_time), phil->id);
		pthread_mutex_unlock(phil->mut_chat);
		pthread_mutex_unlock(phil->left);
		pthread_mutex_unlock(phil->right);
		my_usleep(phil->time_to_sleep);
		gettimeofday(&time, 0);
		pthread_mutex_lock(phil->mut_chat);
		printf("%ld : philo #%d is thinking\n",
			get_time(time, phil->start_time), phil->id);
		pthread_mutex_unlock(phil->mut_chat);
	}
}

void	ft_create_thread(t_all *all, int num)
{
	t_phil	*phil;

	phil = (t_phil *)malloc(sizeof(t_phil));
	phil->id = num;
	phil->time_to_eat = all->time_to_eat;
	phil->time_to_sleep = all->time_to_sleep;
	phil->number_to_eat = all->number_to_eat;
	phil->start_time = all->start_time;
	phil->snack_time = all->start_time;
	phil->left = &(all->mutex[num -1]);
	phil->mut_chat = &all->mut_chat;
	phil->full = 0;
	if (num == all->number_of_phil)
		phil->right = &(all->mutex[0]);
	else
		phil->right = &(all->mutex[num]);
	all->phil[num - 1] = phil;
	pthread_create(&(all->thread[num - 1]), NULL, (void *)life, phil);
}

int	ft_setup_all(t_all *all, int argc, char **argv)
{
	int	check;
	int	i;
	int	num;

	check = 1;
	i = 1;
	while (argv[i])
		check *= ft_is_lit(argv[i++]);
	gettimeofday(&(all->start_time), 0);
	all->number_of_phil = ft_atoi(argv[1]);
	num = all->number_of_phil;
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	all->number_to_eat = -1;
	if (argc == 6)
		all->number_to_eat = ft_atoi(argv[5]);
	all->thread = (pthread_t *)malloc(sizeof(pthread_t) * num);
	all->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	all->phil = (t_phil **)malloc(sizeof(t_phil *) * num);
	if (!check || !all->thread || !all->mutex || !all->phil)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all		*all;
	int			i;
	pthread_t	thread_d;

	if (argc < 5 || argc > 6)
		return (ft_error());
	all = (t_all *)malloc(sizeof(t_all));
	i = ft_setup_all(all, argc, argv);
	if (i == -1)
		return (ft_error());
	while (i < all->number_of_phil)
		pthread_mutex_init(&(all->mutex[i++]), NULL);
	pthread_mutex_init(&all->mut_chat, NULL);
	i = -1;
	while (++i < all->number_of_phil)
		ft_create_thread(all, i + 1);
	pthread_create(&thread_d, NULL, (void *)ft_check_death, all);
	pthread_join(thread_d, NULL);
	ft_freedom(&all);
	return (0);
}

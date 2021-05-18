/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:08:51 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 13:08:53 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_eat(t_phil *phil)
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
	phil->full = 0;
	phil->forks = all->forks;
	phil->chat = all->chat;
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
	all->phil = (t_phil **)malloc(sizeof(t_phil *) * num);
	all->forks = sem_open("forks", O_CREAT, 0666, all->number_of_phil);
	all->chat = sem_open("chat", O_CREAT, 0666, 1);
	if (!check || !all->thread || !all->phil)
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
	sem_unlink("forks");
	sem_unlink("chat");
	all = (t_all *)malloc(sizeof(t_all));
	i = ft_setup_all(all, argc, argv);
	if (i == -1)
		return (ft_error());
	while (i++ < all->number_of_phil)
		ft_create_thread(all, i);
	pthread_create(&thread_d, NULL, (void *)ft_check_death, all);
	pthread_join(thread_d, NULL);
	ft_freedom(&all);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:15:53 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 13:15:57 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_create_phil(t_all *all)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < all->number_of_phil)
	{
		all->id = i + 1;
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			life(all);
		all->pid[i] = pid;
		i++;
	}
	return (0);
}

int	ft_setup_all(t_all *all, int argc, char **argv)
{
	int	check;
	int	i;

	check = 1;
	i = 1;
	while (argv[i])
		check *= ft_is_lit(argv[i++]);
	gettimeofday(&(all->start_time), 0);
	all->snack_time = all->start_time;
	all->number_of_phil = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	all->number_to_eat = -1;
	if (argc == 6)
		all->number_to_eat = ft_atoi(argv[5]);
	all->pid = (pid_t *)malloc(sizeof(pid_t) * all->number_of_phil);
	all->forks = sem_open("forks", O_CREAT, 0666, all->number_of_phil);
	all->chat = sem_open("chat", O_CREAT, 0666, 1);
	all->plague = sem_open("plague", O_CREAT, 0666, 0);
	all->full = sem_open("full", O_CREAT, 0666, 0);
	if (!check || !all->pid || ft_sem_fail(all))
		return (-1);
	return (0);
}

void	*ft_check_full(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->number_of_phil)
	{
		sem_wait(all->full);
		i++;
	}
	sem_post(all->plague);
	return (NULL);
}

void	*ft_check_all_deaths(t_all *all)
{
	sem_wait(all->plague);
	sem_post(all->plague);
	my_usleep(300);
	ft_freedom(&all);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_all		*all;
	int			i;
	pthread_t	thread_d;
	pthread_t	thread_f;

	if (argc < 5 || argc > 6)
		return (ft_error());
	sem_unlink("forks");
	sem_unlink("chat");
	sem_unlink("plague");
	sem_unlink("full");
	all = (t_all *)malloc(sizeof(t_all));
	i = ft_setup_all(all, argc, argv);
	if (i == -1 || ft_create_phil(all) == -1)
		return (ft_error());
	pthread_create(&thread_d, NULL, (void *)ft_check_all_deaths, all);
	if (all->number_to_eat > 0)
		pthread_create(&thread_f, NULL, (void *)ft_check_full, all);
	pthread_join(thread_d, NULL);
	return (0);
}

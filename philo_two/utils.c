/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:09:06 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 13:09:07 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long int	get_time(struct timeval time, struct timeval start_time)
{
	long int	res;

	res = (time.tv_sec - start_time.tv_sec) * 1000;
	res += (time.tv_usec - start_time.tv_usec) / 1000;
	return (res);
}

void	my_usleep(int time_sleep)
{
	struct timeval	time;
	struct timeval	first_time;

	gettimeofday(&time, 0);
	gettimeofday(&first_time, 0);
	while (time_sleep > time.tv_sec * 1000 + time.tv_usec / 1000
		- first_time.tv_sec * 1000 - first_time.tv_usec / 1000)
	{
		usleep(100);
		gettimeofday(&time, 0);
	}
}

int	ft_error(void)
{
	printf("Error\n");
	return (-1);
}

void	ft_freedom(t_all **all)
{
	int	i;

	free((*all)->thread);
	i = 0;
	while (i < (*all)->number_of_phil)
		free((*all)->phil[i++]);
	free((*all)->phil);
	sem_unlink("forks");
	sem_unlink("chat");
	free(*all);
}

int	ft_is_lit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i > 10)
		return (0);
	return (1);
}

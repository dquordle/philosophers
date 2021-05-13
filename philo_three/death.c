/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:16:24 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 13:16:26 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*ft_check_death(t_all *all)
{
	struct timeval	time;

	while (1)
	{
		sem_wait(all->chat);
		gettimeofday(&time, 0);
		if (get_time(time, all->snack_time) >= all->time_to_die)
		{
			printf("%ld : philo #%d died\n",
				get_time(time, all->start_time), all->id);
			sem_post(all->plague);
			sem_post(all->chat);
			exit(0);
		}
		sem_post(all->chat);
	}
}

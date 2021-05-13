/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:08:44 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 13:08:46 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*ft_death(long int time, int num)
{
	printf("%ld : philo #%d died\n", time, num);
	return (NULL);
}

void	*ft_check_death(t_all *all)
{
	struct timeval	time;
	int				i;
	int				full_phil;

	while (1)
	{
		full_phil = 0;
		i = -1;
		gettimeofday(&time, 0);
		while (++i < all->number_of_phil)
		{
			sem_wait(all->chat);
			if (get_time(time, all->phil[i]->snack_time) >= all->time_to_die)
				return (ft_death(get_time(time, all->start_time), i + 1));
			sem_post(all->chat);
			full_phil += all->phil[i]->full;
		}
		if (full_phil == all->number_of_phil)
		{
			sem_wait(all->chat);
			return (NULL);
		}
	}
}

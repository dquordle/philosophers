#include "philo_one.h"

void	*ft_death(long int time, int num)
{
	printf("%ld : philo #%d died\n", time, num);
	return (NULL);
}

void	*ft_check_death(t_all *all)
{
	struct timeval time;
	int	i;
	int	full_phil;

	while (1)
	{
		full_phil = 0;
		i = -1;
		gettimeofday(&time, 0);
		while (++i < all->number_of_phil)
		{
			pthread_mutex_lock(&all->mut_chat);
			if (get_time(time, all->phil[i]->snack_time) >= all->time_to_die)
				return (ft_death(get_time(time, all->start_time), i + 1));
			pthread_mutex_unlock(&all->mut_chat);
			full_phil += all->phil[i]->full;
		}
		if (full_phil == all->number_of_phil)
		{
			pthread_mutex_lock(&all->mut_chat);
			return (NULL);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:09:00 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 13:09:02 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_phil
{
	int				id;
	struct timeval	start_time;
	struct timeval	snack_time;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_to_eat;
	int				full;
	sem_t			*forks;
	sem_t			*chat;
}				t_phil;

typedef struct s_all
{
	pthread_t		*thread;
	t_phil			**phil;
	struct timeval	start_time;
	int				number_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_to_eat;
	sem_t			*forks;
	sem_t			*chat;
}				t_all;

int			ft_atoi(const char *str);
int			ft_is_lit(char *str);
void		ft_freedom(t_all **all);
int			ft_error(void);
void		my_usleep(int time_sleep);
long int	get_time(struct timeval time, struct timeval start_time);
void		*ft_check_death(t_all *all);

#endif

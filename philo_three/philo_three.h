/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:16:37 by dquordle          #+#    #+#             */
/*   Updated: 2021/05/13 13:16:39 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_all
{
	pid_t			*pid;
	struct timeval	start_time;
	struct timeval	snack_time;
	int				number_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_to_eat;
	int				id;
	sem_t			*forks;
	sem_t			*chat;
	sem_t			*plague;
	sem_t			*full;
}				t_all;

int			ft_atoi(const char *str);
int			ft_is_lit(char *str);
void		ft_freedom(t_all **all);
int			ft_error(void);
void		my_usleep(int time_sleep);
long int	get_time(struct timeval time, struct timeval start_time);
void		*ft_check_death(t_all *all);
int			ft_sem_fail(t_all *all);
void		*life(t_all *phil);

#endif

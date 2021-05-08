#include "philo_one.h"

long int	get_time(struct timeval time, struct timeval start_time)
{
	long int res;

	res = (time.tv_sec - start_time.tv_sec) * 1000;
	res += (time.tv_usec - start_time.tv_usec) / 1000;
	return (res);
}

void	my_usleep(int time_sleep)
{
	struct timeval time;
	struct timeval first_time;

	gettimeofday(&time, 0);
	gettimeofday(&first_time, 0);
	while (time_sleep > time.tv_sec * 1000 + time.tv_usec / 1000 - first_time.tv_sec * 1000 - first_time.tv_usec / 1000)
	{
		usleep(100);
		gettimeofday(&time, 0);
//		printf("%d\n", time.tv_usec);
	}
}

void	*lets_get_this_bread(void *shit)
{
	int eaten = 0;
	t_phil *phil;
	struct timeval time;

	phil = (t_phil *)shit;
	usleep(((phil->id - 1) % 2) * 100);
//	printf("lol\n");
//	while (i++ < 5)
//		printf("%d\n", phil->id);
	while (1)
	{
		pthread_mutex_lock(phil->left);
		gettimeofday(&time, 0);
		pthread_mutex_lock(phil->mut_chat);
		printf("%ld : philo #%d has taken a fork\n", get_time(time, phil->start_time), phil->id);
		pthread_mutex_unlock(phil->mut_chat);
		pthread_mutex_lock(phil->right);
		gettimeofday(&time, 0);
		pthread_mutex_lock(phil->mut_chat);
		phil->snack_time = time;
		printf("%ld : philo #%d has taken a fork\n", get_time(time, phil->start_time), phil->id);
//		gettimeofday(&time, 0);
		printf("%ld : philo #%d is eating\n", get_time(time, phil->start_time), phil->id);
		pthread_mutex_unlock(phil->mut_chat);
		eaten++;
		my_usleep(phil->time_to_eat);
		gettimeofday(&time, 0);
		pthread_mutex_lock(phil->mut_chat);
		printf("%ld : philo #%d is sleeping\n",get_time(time, phil->start_time), phil->id);
		pthread_mutex_unlock(phil->mut_chat);
		pthread_mutex_unlock(phil->left);
		pthread_mutex_unlock(phil->right);
		my_usleep(phil->time_to_sleep);
		gettimeofday(&time, 0);
		pthread_mutex_lock(phil->mut_chat);
		printf("%ld : philo #%d is thinking\n", get_time(time, phil->start_time), phil->id);
		pthread_mutex_unlock(phil->mut_chat);
	}
}

void	*ft_create_thread(t_all *all, int num)
{
	t_phil *phil;

	phil = (t_phil *)malloc(sizeof(t_phil));
	phil->id = num;
	phil->time_to_eat = all->time_to_eat;
	phil->time_to_sleep = all->time_to_sleep;
	phil->number_to_eat = all->number_to_eat;
	phil->start_time = all->start_time;
	phil->snack_time = all->start_time;
	phil->left = &(all->mutex[num -1]);
	phil->mut_chat = &all->mut_chat;
	if (num == all->number_of_phil)
		phil->right = &(all->mutex[0]);
	else
		phil->right = &(all->mutex[num]);
	all->phil[num - 1] = phil;
	pthread_create(&(all->thread[num - 1]), NULL, lets_get_this_bread, (void *)phil);
}

void	*ft_check_death(t_all *all)
{
//	t_all *all;
	struct timeval time;
	int	i;

//	all = (t_all *)alll;
	while (1)
	{
		i = -1;
		gettimeofday(&time, 0);
		while (++i < all->number_of_phil)
		{
			pthread_mutex_lock(&all->mut_chat);
			if (get_time(time, all->phil[i]->snack_time) >= all->time_to_die)
			{
//				all->death = 1;
				printf("%ld : philo #%d is dead\n", get_time(time, all->start_time), i + 1);
				return (NULL);
//				int j = 0;
//				while (j < all->number_of_phil)
//					pthread_mutex_lock(&(all->mutex[j++]));
			}
			pthread_mutex_unlock(&all->mut_chat);
		}
	}
}

//number_of_philosophers, time_to_die, time_to_eat,
//		time_to_sleep, [number_of_times_each_philosopher_must_eat]

int main(int argc, char **argv)
{
//	struct timeval time;
	t_all *all;
//	pthread_t *thread;
	int i;
//	int number_of_phil;
//	int	time_to_die;
//	int time_to_eat;
//	int time_to_sleep;
//	int number_to_eat;
//	pthread_mutex_t *mutex;

	if (argc < 5 || argc > 6)
		exit(1);
////    validate
	all = (t_all *)malloc(sizeof(t_all));
	gettimeofday(&(all->start_time), 0);
//	printf("%d\n", all->start_time.tv_usec);
//	number_of_phil = ;
	all->number_of_phil = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	all->number_to_eat = -1;
	if (argc == 6)
		all->number_to_eat = ft_atoi(argv[5]);
	all->thread = (pthread_t *)malloc(sizeof(pthread_t) * all->number_of_phil);
	all->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * all->number_of_phil);
	all->phil = (t_phil **)malloc(sizeof(t_phil *) * all->number_of_phil);
	i = 0;
	while (i < all->number_of_phil)
		pthread_mutex_init(&(all->mutex[i++]), NULL);
	pthread_mutex_init(&all->mut_chat, NULL);
	i = -1;
	pthread_t thread_d;
	pthread_create(&thread_d, NULL, (void *)ft_check_death, all);
	while (++i < all->number_of_phil)
		ft_create_thread(all, i + 1);
	pthread_join(thread_d, NULL);
//	printf("%d\n", time.tv_usec);
	return (0);
}













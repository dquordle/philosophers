#include "philo_one.h"

//number_of_philosophers, time_to_die, time_to_eat,
//		time_to_sleep, [number_of_times_each_philosopher_must_eat]

long int	time_calc(struct timeval time, struct timeval start_time)
{
	long int res;

	res = (time.tv_sec - start_time.tv_sec) * 1000;
	res += (time.tv_usec - start_time.tv_usec) / 1000;
	return (res);
}

void	*lets_get_this_bread(void *shit)
{
	int i = 0;
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
		printf("%ld : philo #%d has taken a fork\n", time_calc(time, phil->start_time), phil->id);
		pthread_mutex_lock(phil->right);
		gettimeofday(&time, 0);
		printf("%ld : philo #%d has taken a fork\n", time_calc(time, phil->start_time), phil->id);
		gettimeofday(&time, 0);
		printf("%ld : philo #%d is eating\n", time_calc(time, phil->start_time), phil->id);
		usleep(10000);
		pthread_mutex_unlock(phil->left);
		pthread_mutex_unlock(phil->right);
		gettimeofday(&time, 0);
		printf("%ld : philo #%d is sleeping\n",time_calc(time, phil->start_time), phil->id);
		usleep(20000);
		gettimeofday(&time, 0);
		printf("%ld : philo #%d is thinking\n", time_calc(time, phil->start_time), phil->id);
	}
}

//void	ft_mutex_init(t_all *all, int num)
//{
//	int i;
//
//	all->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
//	i = 0;
//	while (i < num)
//		pthread_mutex_init(&(all->mutex[i++]), NULL);
//
//}

void	*ft_create_thread(t_all *all, int num)
{
	t_phil *phil;

	phil = (t_phil *)malloc(sizeof(t_phil));
	phil->id = num;
	phil->start_time = all->start_time;
	phil->left = &(all->mutex[num -1]);
	if (num == all->number_of_phil)
		phil->right = &(all->mutex[0]);
	else
		phil->right = &(all->mutex[num]);
	all->phil[num - 1] = phil;
	pthread_create(&(all->thread[num - 1]), NULL, lets_get_this_bread, (void *)phil);
}

int main(int argc, char **argv)
{
//	struct timeval time;
	t_all *all;
//	pthread_t *thread;
	int i;
	int number_of_phil;
//	pthread_mutex_t *mutex;

//	if (argc < 5 || argc > 6)
//		ft_error();
////    validate
	all = (t_all *)malloc(sizeof(t_all));
	gettimeofday(&(all->start_time), 0);
//	printf("%d\n", all->start_time.tv_usec);
	number_of_phil = ft_atoi(argv[1]);
	all->number_of_phil = number_of_phil;
	all->thread = (pthread_t *)malloc(sizeof(pthread_t) * number_of_phil);
	all->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number_of_phil);
	all->phil = (t_phil **)malloc(sizeof(t_phil *) * number_of_phil);
	i = 0;
	while (i < number_of_phil)
		pthread_mutex_init(&(all->mutex[i++]), NULL);
	i = -1;
	while (++i < number_of_phil)
		ft_create_thread(all, i + 1);
	i = -1;
	while (++i < number_of_phil)
		pthread_join(all->thread[i], NULL);
//	printf("%d\n", time.tv_usec);
	return (0);
}













#include "philo.h"

static void take_forks(t_philo *philo)
{
	t_all   *all;
	long    ts;

	all = philo->all;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&all->print_mutex);
		ts = timestamp() - all->start_time;
		printf("%ld %d has taken a fork\n", ts, philo->id);
		pthread_mutex_unlock(&all->print_mutex);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&all->print_mutex);
		ts = timestamp() - all->start_time;
		printf("%ld %d has taken a fork\n", ts, philo->id);
		pthread_mutex_unlock(&all->print_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&all->print_mutex);
		ts = timestamp() - all->start_time;
		printf("%ld %d has taken a fork\n", ts, philo->id);
		pthread_mutex_unlock(&all->print_mutex);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&all->print_mutex);
		ts = timestamp() - all->start_time;
		printf("%ld %d has taken a fork\n", ts, philo->id);
		pthread_mutex_unlock(&all->print_mutex);
	}
}

static void eat(t_philo *philo)
{
	t_all   *all = philo->all;
	long    ts;

	pthread_mutex_lock(&all->print_mutex);
	ts = timestamp() - all->start_time;
	printf("%ld %d is eating\n", ts, philo->id);
	pthread_mutex_unlock(&all->print_mutex);
	philo->last_meal = timestamp();
	philo->eat_count++;
	precise_sleep(all->time_to_eat);
}

static void sleep_and_think(t_philo *philo)
{
	t_all   *all = philo->all;
	long    ts;

	pthread_mutex_lock(&all->print_mutex);
	ts = timestamp() - all->start_time;
	printf("%ld %d is sleeping\n", ts, philo->id);
	pthread_mutex_unlock(&all->print_mutex);
	precise_sleep(all->time_to_sleep);
	pthread_mutex_lock(&all->print_mutex);
	ts = timestamp() - all->start_time;
	printf("%ld %d is thinking\n", ts, philo->id);
	pthread_mutex_unlock(&all->print_mutex);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_all	*all = philo->all;

	while (!all->someone_died &&
		  (all->must_eat_count < 0 || philo->eat_count < all->must_eat_count))
	{
		take_forks(philo);
		eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleep_and_think(philo);
	}
	return (NULL);
}

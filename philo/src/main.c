#include "philo.h"

int main(int argc, char **argv)
{
	t_all		all;
	pthread_t	monitor;
	int			i;

	i = init_all(&all, argc, argv);
	if (i > 0)
		return (1);
	all.start_time = timestamp();
	all.someone_died = 0;
	i = -1;
	while (++i < all.nb_philo)
		pthread_create(&all.philos[i].thread, NULL, philosopher_routine, &all.philos[i]);
	pthread_create(&monitor, NULL, monitor_routine, &all);
	i = -1;
	while (++i < all.nb_philo)
		pthread_join(all.philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	// Cleanup (forks, philos, mutexes) burada yapılacak
	return (0);
}

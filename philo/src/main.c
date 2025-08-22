#include "philo.h"

int main(int argc, char **argv)
{
	t_all		all;
	pthread_t	monitor;
	int			i;

	i = init_all(&all, argc, argv);
	if (i > 0)
		return (1);
	if (all.nb_philo == 1)
	{
		pthread_create(&all.philos[0].thread, NULL, single_philosopher_routine, &all.philos[0]);
		pthread_create(&monitor, NULL, monitor_routine, &all);
		pthread_join(all.philos[0].thread, NULL);
		pthread_join(monitor, NULL);
	}
	else
	{
		i = -1;
		while (++i < all.nb_philo)
			pthread_create(&all.philos[i].thread, NULL, philosopher_routine, &all.philos[i]);
		pthread_create(&monitor, NULL, monitor_routine, &all);
		i = -1;
		while (++i < all.nb_philo)
			pthread_join(all.philos[i].thread, NULL);
		pthread_join(monitor, NULL);
	}
	cleanup_all(&all);
	return (0);
}

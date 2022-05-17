#include "philo.h"

void	exit_ph(t_rules *rules, t_philo *philo)
{
    int	i;

	i = 0;
	while (i++ < rules->number_of_ph)
		pthread_join(philo[i].thread_id, NULL);
	i = 0;
	while (i++ < rules->number_of_ph)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->write));
}
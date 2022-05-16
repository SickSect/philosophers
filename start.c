#include "philo.h"

void *thread_process(void *void_philo)
{

}

int	start(t_rules *rule)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = rule->philosophers;
	rule->time = timestamp();
	while (i < rule->number_of_ph)
	{
		if (pthread_create(&(ph[i].thread_id), NULL, thread_process, &(ph[i])))
			return (1);
		ph[i].ate = timestamp();
		i++;
	}
}
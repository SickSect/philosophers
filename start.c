#include "philo.h"

void	eating(t_philo *philo)
{

}

void	*thread_process(void *void_philo)
{
	int		i;
	t_philo	*philo;
	t_rules	*rule;

	i = 0;
	philo = (t_philo *)void_philo;
	rule = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rule->dead))
	{
		eating(philo);
		if (rule->well_fed)
			break ;
	}
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
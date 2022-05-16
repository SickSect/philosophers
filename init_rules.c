#include "philo.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->number_of_ph;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->think), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal), NULL))
		return (1);
	return (0);
}

int	init_philo(t_rules *rules)
{
	int	i;

	i = rules->number_of_ph;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].left_fork = i;
		rules->philosophers[i].right_fork = (i + 1) % rules->number_of_ph;
		rules->philosophers[i].rules = rules;
		rules->philosophers[i].ate = 0;
	}
	return (0);
}

int	init_rules(t_rules *rule, char **argv)
{
	rule->number_of_ph = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_to_eat = ft_atoi(argv[3]);
	rule->time_to_sleep = ft_atoi(argv[4]);
	rule->dead = 0;
	rule->well_fed = 0;
	if (rule->number_of_ph < 2 || rule->time_to_die < 0
		|| rule->time_to_eat < 0 || rule->time_to_sleep < 0
		|| rule->number_of_ph > 250)
		return (-1);
	if (argv[5])
	{
		rule->must_eat = ft_atoi(argv[5]);
		if (rule->must_eat <= 0)
			return (-1);
	}
	else
		rule->must_eat = -1;
	return (0);
}
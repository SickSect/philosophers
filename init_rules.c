#include "philo.h"

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
		|| rule->number_of_ph > 250);
		return (-1);
	
}
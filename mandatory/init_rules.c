#include "philo.h"

static int	init_rules(t_rules *rule, char **argv)
{
	rule->philo_amount = ft_atoi(argv[1]);
	rule->death_timer = ft_atoi(argv[2]);
	rule->eat_timer = ft_atoi(argv[3]);
	rule->sleep_timer = ft_atoi(argv[4]);
	rule->amount_fed_philo = 0;
	rule->death_status = 0;
	if (rule->philo_amount < 0 || rule->death_timer < 0 || rule->eat_timer < 0
		|| rule->sleep_timer < 0 || rule->philo_amount > 250)
		return (-2);
	if (argv[5])
	{
		rule->max_meal = ft_atoi(argv[5]);
		if (rule->max_meal <= 0)
			return (-1);
	}
	else
		rule->max_meal = -1;
	return (0);
}

static int	init_philo(t_rules *rules)
{
	int	i;

	i = rules->philo_amount;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].ate = 0;
		rules->philosophers[i].last_meal_timer = 0;
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->philo_amount;
		rules->philosophers[i].rules = rules;
	}
	return (0);
}

static int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->philo_amount;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks_mutex[i]), NULL))
			return (-2);
	}
	if (pthread_mutex_init(&(rules->write_mutex), NULL))
		return (-2);
	if (pthread_mutex_init(&(rules->write_mutex), NULL))
		return (-2);
	return (0);
}

int	initialisation(t_rules *rule, char **argv)
{
	int	init;

	init = init_rules(rule, argv);
	if (init != 0)
	{
		if (init == -2)
			err("Wrong argument");
		else
			err("There is an error at initialisation terms");
		return (init);
	}
	init_philo(rule);
	init = init_mutex(rule);
	if (init != 0)
	{
		err("There is an error at creating mutex");
		return (init);
	}
	return (0);
}
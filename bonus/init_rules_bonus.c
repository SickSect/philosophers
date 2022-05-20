#include "philo_bonus.h"

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

static int	init_semaphore(t_rules *rules)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_meal");
	rules->forks_sem = sem_open("/philo_forks", O_CREAT, S_IRWXU, rules->philo_amount);
	rules->write_sem = sem_open("/philo_write", O_CREAT, S_IRWXU, 1);
	rules->meal_sem = sem_open("/philo_meal", O_CREAT, S_IRWXU, 1);
	
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
	init = init_semaphore(rule);
	if (init != 0)
	{
		err("There is an error at creating semaphore");
		return (init);
	}
	return (0);
}
#include "philo.h"

void	memento_mori(t_rules *rule, t_philo *philo)
{
	int	i;
	while(!(rule->dead))
	{
		i = 0;
		while (i++ < rule->number_of_ph && !(rule->dead))
		{
			pthread_mutex_lock(&(rule->meal));
			if (diff_timer(philo[i].ate, timestamp()) > rule->time_to_die)
			{
				act_printer(rule, i, "died");
				rule->dead = 1;
			}
			pthread_mutex_unlock(&(rule->meal));
			usleep(100);
		}
		if (rule->dead)
			break;
		i = 0;
		while (rule->well_fed != -1 && i < rule->number_of_ph && philo[i].ate >= rule->number_of_ph)
			i++;
		if (i == rule->number_of_ph)
			rule->well_fed = 1;
	}
}

void	eating(t_philo *philo)
{
	t_rules *rule;

	rule = philo->rules;
	pthread_mutex_lock(&(rule->forks[philo->left_fork]));
	act_printer(rule, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rule->forks[philo->right_fork]));
	act_printer(rule, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rule->meal));
	act_printer(rule, philo->id, "is eating");
	philo->meal_timestamp = timestamp();
	pthread_mutex_unlock(&(rule->meal));
	sleeping(rule->time_to_eat, rule);
	(philo->ate)++;
	pthread_mutex_unlock(&(rule->forks[philo->left_fork]));
	pthread_mutex_unlock(&(rule->forks[philo->right_fork]));
}

void	sleeping(int time_to_sleep, t_rules* rule)
{
	long long	i;

	i = timestamp();
	while (!(rule->dead))
	{
		if (diff_timer(i, timestamp()) >= time_to_sleep)
			break ;
		usleep(50);
	}
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
		act_printer(rule, philo->id, "is sleeping");
		sleeping(rule->time_to_sleep, rule);
		act_printer(rule, philo->id, "is thinking");
		i++;
	}
	return (0);
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
	memento_mori(rule, ph);
	exit_ph(rule, ph);
	return (0);
}
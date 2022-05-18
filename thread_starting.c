#include "philo.h"
static void	eating(t_philo *ph)
{
	t_rules	*rule;

	rule = ph->rules;
	pthread_mutex_lock(&(rule->forks_mutex[ph->left_fork_id]));
	print_action("has taken a fork", rule, ph->id);
	pthread_mutex_lock(&(rule->forks_mutex[ph->right_fork_id]));
	print_action("has taken a fork", rule, ph->id);
	pthread_mutex_lock(&(rule->meal_mutex));
	print_action("is eating", rule, ph->id);
	ph->last_meal_timer = moment();
	pthread_mutex_unlock(&(rule->meal_mutex));
	doing(rule->eat_timer, rule);
	(ph->ate)++;
	pthread_mutex_unlock(&(rule->forks_mutex[ph->left_fork_id]));
	pthread_mutex_unlock(&(rule->forks_mutex[ph->right_fork_id]));
}

static void *process(void *void_ph)
{
	int		i;
	t_philo	*ph;
	t_rules	*rule;

	i = 0;
	ph = (t_philo *) void_ph;
	rule = ph->rules;
	if (ph->id % 2)
		usleep(15000);
	while (!(rule->death_status))
	{
		eating(ph);
		if (rule->amount_fed_philo)
	}
	return (NULL);
}

int	thread_starting(t_rules *rules)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = rules->philosophers;
	rules->first_time = moment();
	while (i < rules->philo_amount)
	{
		if (pthread_create(&(ph[i].thread_id), NULL, process, &(ph[i])))
			return (-1);
		ph[i].last_meal_timer = moment();
		i++;
	}
}

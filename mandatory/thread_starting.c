#include "philo.h"

static void	leave(t_rules *rule, t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < rule->philo_amount)
		pthread_join(ph[i].thread_id, NULL);
	i = rule->philo_amount;
	while (--i >= 0)
		pthread_mutex_destroy(&(rule->forks_mutex[i]));
	pthread_mutex_destroy(&(rule->write_mutex));
	pthread_mutex_destroy(&(rule->meal_mutex));
}

static void	if_death(t_rules *rule, t_philo *ph)
{
	int	i;

	while (!(rule->amount_fed_philo))
	{
		i = -1;
		while (++i < rule->philo_amount && !(rule->death_status))
		{
			pthread_mutex_lock(&(rule->meal_mutex));
			if (cut_moment(ph[i].last_meal_timer, moment()) > rule->death_timer)
			{
				print_action("died", rule, i);
				rule->death_status = 1;
			}
			pthread_mutex_unlock(&(rule->meal_mutex));
			usleep(100);
		}
		if (rule->death_status)
			break ;
		i = 0;
		while (rule->max_meal != -1 && i < rule->philo_amount && ph[i].ate >= rule->max_meal)
			i++;
		if (i == rule->philo_amount)
			rule->amount_fed_philo = 1;
	}
}

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

static void	*process(void *void_ph)
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
			break ;
		print_action("is sleeping", rule, ph->id);
		doing(rule->sleep_timer, rule);
		print_action("is thinking", rule, ph->id);
		i++;
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
	if_death(rules, ph);
	leave(rules, ph);
	return (0);
}

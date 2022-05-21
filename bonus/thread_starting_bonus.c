#include "philo_bonus.h"

static void	leave(t_rules *rule, t_philo *ph)
{
	int	i;

	i = 0;
	while (i++ < rule->philo_amount)
		pthread_join(ph[i].thread_id, NULL);
	sem_close(rule->forks_sem);
	sem_close(rule->write_sem);
	sem_close(rule->meal_sem);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_meal");
}

static void	if_death(t_rules *rule, t_philo *ph)
{
	int	i;

	while (!(rule->amount_fed_philo))
	{
		i = -1;
		while (++i < rule->philo_amount && !(rule->death_status))
		{
			sem_wait(rule->meal_sem);
			if (cut_moment(ph[i].last_meal_timer, moment()) > rule->death_timer)
			{
				print_action("died", rule, i);
				rule->death_status = 1;
			}
			sem_post(rule->meal_sem);
			usleep(100);
		}
		if (rule->death_status)
			break ;
		i = 0;
		while (rule->max_meal != -1 && i < rule->philo_amount
			&& ph[i].ate >= rule->max_meal)
			i++;
		if (i == rule->philo_amount)
			rule->amount_fed_philo = 1;
	}
}

static void	eating(t_philo *ph)
{
	t_rules	*rule;

	rule = ph->rules;
	sem_wait(rule->forks_sem);
	print_action("has taken a fork", rule, ph->id);
	sem_wait(rule->forks_sem);
	print_action("has taken a fork", rule, ph->id);
	sem_wait(rule->meal_sem);
	print_action("is eating", rule, ph->id);
	ph->last_meal_timer = moment();
	sem_post(rule->meal_sem);
	doing(rule->eat_timer, rule);
	(ph->ate)++;
	sem_post(rule->forks_sem);
	sem_post(rule->forks_sem);
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

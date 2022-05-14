#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philo
{
	int			left_fork;
	int			right_fork;
	int			id;
	int			ate;
	struct s_rules		*rules;
	pthread_t	thread_id;
}	t_philo;

typedef struct s_rules
{
	int	number_of_ph;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_each_eat;
	int	dead;
	int	well_fed;
	int	must_eat;
}	t_rules;

long long	ft_atoi(const char *str);
int	init_rules(t_rules *rule, char **argv);
#endif
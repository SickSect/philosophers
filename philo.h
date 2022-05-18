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
	pthread_t		thread_id;
	long long		last_meal_timer;
	int				id;
	int				ate;
	int				left_fork_id;
	int				right_fork_id;
	struct s_rules	*rules;	
}	t_philo;

typedef struct s_rules
{
	long long		first_time;
	int				eat_timer;
	int				sleep_timer;
	int				death_timer;
	int				philo_amount;
	int				max_meal;
	int				death_status;
	int				amount_fed_philo;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	forks_mutex[250];
	t_philo			philosophers[250];
}	t_rules;

long long	ft_atoi(const char *str);
long long	timestamp(void);
int			initialisation(t_rules *rule, char **argv);
void		err(char *error);
long long	moment(void);
long long	cut_moment(long long before, long long after);\
void		doing(long long time, t_rules *rule);
void		print_action(char *action, t_rules *rule, int id);
#endif
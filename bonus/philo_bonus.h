/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:14:36 by ugina             #+#    #+#             */
/*   Updated: 2022/05/25 11:14:38 by ugina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

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
	sem_t			*write_sem;
	sem_t			*meal_sem;
	sem_t			*forks_sem;
	t_philo			philosophers[250];
}	t_rules;

long long	ft_atoi(const char *str);
long long	timestamp(void);
int			initialisation(t_rules *rule, char **argv);
void		err(char *error);
long long	moment(void);
long long	cut_moment(long long before, long long after);
void		doing(long long time, t_rules *rule);
void		print_action(char *action, t_rules *rule, int id);
int			thread_starting(t_rules *rules);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_proc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:14:58 by ugina             #+#    #+#             */
/*   Updated: 2022/05/25 11:14:59 by ugina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	doing(long long time, t_rules *rule)
{
	long long	i;

	i = moment();
	while (!(rule->death_status))
	{
		if (cut_moment(i, moment()) >= time)
			break ;
		usleep(50);
	}
}

void	print_action(char *action, t_rules *rule, int id)
{
	sem_wait(rule->write_sem);
	if (!(rule->death_status))
	{
		printf("%lli ", moment() - rule->first_time);
		printf("%i ", id + 1);
		printf("%s\n", action);
	}
	sem_post(rule->write_sem);
	return ;
}

long long	moment(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	cut_moment(long long before, long long after)
{
	return (after - before);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:13:34 by ugina             #+#    #+#             */
/*   Updated: 2022/05/25 11:13:36 by ugina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err(char *error)
{
	int	len;

	len = 0;
	while (error[len])
		len++;
	write(2, "Error: ", 7);
	write(2, error, len);
	write(2, "\n", 1);
}

int	main(int argc, char **argv)
{
	t_rules	rule;
	int		init;

	if (argc != 5 && argc != 6)
	{
		err("Wrong amount of arguments!");
		return (-1);
	}
	init = initialisation(&rule, argv);
	if (init != 0)
		return (init);
	moment();
	init = thread_starting(&rule);
	return (0);
}

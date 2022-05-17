#include "philo.h"

void act_printer(t_rules *rule, int id, char *str)
{
	pthread_mutex_lock(&(rule->write));
	if (!(rule->dead))
	{
		printf("%lli ", timestamp() - rule->time);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(rule->write));
	return ;
}

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
	init = init_rules(&rule, argv);
	if ((init = init_mutex(&rule)))
	{
		err("There was an error creating mutex");
		return (init);
	}
	init = init_philo(&rule);
	if (start(&rule))
	{
		err("There was an error creating the threads");
		return (init);
	}
	return (0);
}
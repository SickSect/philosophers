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
	init = init_rules(&rule, argv);
	if (init_mutex(&rule))
		return (2);
}
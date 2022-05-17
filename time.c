#include "philo.h"

long long	diff_timer(long long prev, long long next)
{
	return (next - prev);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
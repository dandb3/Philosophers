#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx])
		++idx;
	return (idx);
}

t_milisec	starve_time(struct timeval *start_time, struct timeval *cur_time)
{
	t_milisec	time_spent;

	time_spent = 0;
	time_spent += 1000 * (cur_time->tv_sec - start_time->tv_sec);
	time_spent += (cur_time->tv_usec - start_time->tv_usec) / 1000;
	return (time_spent);
}

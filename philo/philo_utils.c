#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	idx;

	idx = 0;
	while (*(str++))
		++idx;
	return (idx);
}

t_milisec	time_interval(struct timeval *start_time, struct timeval *cur_time)
{
	return ((cur_time->tv_sec - start_time->tv_sec) * 1000
		+ (cur_time->tv_usec - start_time->tv_usec) / 1000);
}

int	philo_atoi(const char *str)
{
	long long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *(str++) - '0';
		if (result > 2147483647)
			return (RET_FAILURE);
	}
	if (*str != '\0' || result == 0)
		return (RET_FAILURE);
	return (result);
}

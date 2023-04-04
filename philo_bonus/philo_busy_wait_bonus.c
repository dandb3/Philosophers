#include "philo_bonus.h"

static int	die_check(t_info *info, struct timeval *cur_time)
{
	if ()
}

int	busy_wait(t_info *info, t_milisec duration)
{
	struct timeval	cur_time;

	gettimeofday(&info->wait_start, NULL);
	while (1)
	{
		usleep(300);
		gettimeofday(&cur_time, NULL);
		if (die_check(info, &cur_time))
	}
}

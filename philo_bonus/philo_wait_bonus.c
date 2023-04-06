#include "philo_bonus.h"

void	busy_wait(t_info *info, t_milisec duration)
{
	while (1)
	{
		usleep(300);
		gettimeofday(&info->cur_time, NULL);
		if (time_interval(&info->wait_start, &info->cur_time) >= duration)
			return ;
	}
}

void	hold_forks(t_info *info)
{
	sem_wait(info->resource->forks_access);
	sem_wait(info->resource->forks_status);
	gettimeofday(&info->cur_time, NULL);
	print_msg(info, MSG_FORK);
	sem_wait(info->resource->forks_status);
	print_msg(info, MSG_FORK);
	sem_post(info->resource->forks_access);
}

void	drop_forks(t_info *info)
{
	sem_post(info->resource->forks_status);
	sem_post(info->resource->forks_status);
}

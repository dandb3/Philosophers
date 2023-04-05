#include "philo_bonus.h"

static int	die_check(t_info *info, struct timeval *cur_time)
{
	if (time_interval(&info->last_eat, cur_time) >= info->input->time_to_die)
		return (DEAD);
	return (ALIVE);
}

void	busy_wait(t_info *info, t_milisec duration)
{
	struct timeval	cur_time;

	gettimeofday(&info->wait_start, NULL);
	while (1)
	{
		usleep(300);
		gettimeofday(&cur_time, NULL);
		if (die_check(info, &cur_time) == DEAD)
			print_msg(info, MSG_DIED, MODE_DIED);
		if (time_interval(&info->wait_start, &cur_time) >= duration)
			return ;
	}
}

void	hold_forks(t_info *info)
{
	struct timeval	cur_time;

	while (1)
	{
		gettimeofday(&cur_time, NULL);
		if (die_check(info, &cur_time) == DEAD)
			print_msg(info, MSG_DIED, MODE_DIED);
		sem_wait(info->resource->forks_access);
		if (info->resource->status == AVAILABLE)
		{
			info->resource->status = USING;
			sem_post(info->resource->forks_access);
			sem_wait(info->resource->forks_status);
			print_msg(info, MSG_FORK, MODE_FORK);
			sem_wait(info->resource->forks_status);
			print_msg(info, MSG_FORK, MODE_FORK);
			return ;
		}
		sem_post(info->resource->forks_access);
		usleep(300);
	}
}

void	release_forks(t_info *info)
{
	sem_wait(info->resource->forks_access);
	
}

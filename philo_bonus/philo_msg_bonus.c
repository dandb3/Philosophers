#include "philo_bonus.h"

void	print_msg(t_info *info, const char *msg)
{
	struct timeval	cur_time;
	t_milisec		timestamp;

	gettimeofday(&cur_time, NULL);
	timestamp = time_interval(&info->start_time, &cur_time);
	sem_wait(info->resource->sem_print);
	printf("%d %d%s\n", timestamp, info->pos, msg);
	sem_post(info->resource->sem_print);
}

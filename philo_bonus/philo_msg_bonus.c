#include "philo_bonus.h"

void	print_msg(t_info *info, const char *msg, t_mode mode)
{
	struct timeval	cur_time;
	t_milisec		timestamp;

	gettimeofday(&cur_time, NULL);
	timestamp = time_interval(&info->start_time, &cur_time);
	sem_wait(info->resource->sem_print);
	printf("%d %d%s\n", timestamp, info->pos, msg);
	if (mode == MODE_DIED)
	{
		free_resource();
		kill(0, SIGKILL);
	}
	sem_post(info->resource->sem_print);
	if (mode == MODE_EAT && ++(info->eat_cnt) == info->input->number_of_times)
		sem_post(info->resource->full_counter);
}

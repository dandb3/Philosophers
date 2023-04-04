#include "philo_bonus.h"

void	philo_begin(t_info *info)
{
	pthread_t	full_monitor;
	int			idx;

	idx = -1;
	while (++idx < info->input->philo_num)
	{
		info->pid_arr[idx] = fork();
		if (info->pid_arr[idx] == 0)
			break;
	}
	if (info->pid_arr[idx] == 0)
		philo_routine(info);
	else
		philo_manage(info);
}

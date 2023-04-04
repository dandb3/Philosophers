#include "philo_bonus.h"

static void	*full_monitor(void *void_info)
{
	t_info	*info;
	int		idx;

	info = (t_info *) void_info;
	idx = -1;
	while (++idx < info->input->philo_num)
		sem_wait(info->resource->full_counter);
	idx = -1;
	while (++idx < info->input->philo_num)
		kill(info->pid_arr[idx], SIGKILL);
	return ((void *)RET_SUCCESS);
}

void	philo_manage(t_info *info)
{
	pthread_t	full_monitor_thread;
	pid_t		died_process;
	int			idx;
	int			status;

	pthread_create(&full_monitor_thread, NULL, full_monitor, info);
	pthread_detach(full_monitor_thread);
	died_process = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		idx = -1;
		while (++idx < info->input->philo_num)
			if (info->pid_arr[idx] != died_process)
				kill(info->pid_arr[idx], SIGKILL);
	}
	idx = 0;
	while (++idx < info->input->philo_num)
		waitpid(-1, NULL, 0);
}

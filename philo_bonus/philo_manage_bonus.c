#include "philo_bonus.h"

static void	*full_monitor(void *void_info)
{
	t_info	*info;
	int		idx;

	info = (t_info *) void_info;
	idx = -1;
	while (++idx < info->input->philo_num)
		sem_wait(info->resource->full_counter);
	sem_wait(info->resource->sem_print);
	idx = -1;
	while (++idx < info->input->philo_num)
		kill(info->resource->pid_arr[idx], SIGKILL);
	return ((void *)RET_SUCCESS);
}

static void	die_msg_and_kill(t_info *info, pid_t dead_pid)
{
	int				idx;

	gettimeofday(&info->cur_time, NULL);
	idx = -1;
	while (++idx < info->input->philo_num)
	{
		if (info->resource->pid_arr[idx] == dead_pid)
			printf("%d %d%s\n", time_interval(&info->start_time,
				&info->cur_time), idx + 1, MSG_DIED);
		else
			kill(info->resource->pid_arr[idx], SIGKILL);
	}
}

void	philo_manage(t_info *info)
{
	pthread_t	full_monitor_thread;
	pid_t		dead_pid;
	int			idx;
	int			status;

	pthread_create(&full_monitor_thread, NULL, full_monitor, info);
	pthread_detach(full_monitor_thread);
	dead_pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		die_msg_and_kill(info, dead_pid);
	idx = 0;
	while (++idx < info->input->philo_num)
		waitpid(-1, NULL, 0);
}

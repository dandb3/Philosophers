#include "philo.h"

int	print_msg(t_philo *philo_data, const char *msg, t_mode mode)
{
	struct timeval	cur_time;

	pthread_mutex_lock(philo_data->mutex_die_checker);
	if (*philo_data->die_cnt == DEAD)
	{
		pthread_mutex_unlock(philo_data->mutex_die_checker);
		return (RET_FAILURE);
	}
	gettimeofday(&cur_time, NULL);
	printf("%d %d%s", time_interval(philo_data->survive_start, &cur_time), philo_data->pos, msg);
	if (mode == MODE_EAT)
	{
		philo_data->starve_start = cur_time;
		if (++(philo_data->eat_cnt) == philo_data->input->number_of_times)
			if (++(*philo_data->die_cnt) == philo_data->input->philo_num)
				*philo_data->die_cnt = DEAD;
	}
	pthread_mutex_unlock(philo_data->mutex_die_checker);
	return (RET_SUCCESS);
}

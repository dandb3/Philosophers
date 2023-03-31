#include "philo.h"

static void	*survive(void *philo)
{
	t_philo	*philo_data;

	philo_data = (t_philo *) philo;
	print_msg(philo_data, MSG_THINK, MODE_THINK);
	if (philo_data->input->philo_num == 1)
	{
		print_msg(philo_data, MSG_FORK, MODE_FORK);
		return ((void *)RET_SUCCESS);
	}
	if (philo_data->pos % 2 == 0)
		usleep(DELAY);
	return (routine(philo_data));
}

static void	death_monitor(t_input *input, t_resource *resource, t_philo *philo_data)
{
	struct timeval	cur_time;
	t_milisec		timestamp;
	int				idx;

	while (1)
	{
		idx = -1;
		gettimeofday(&cur_time, NULL);
		timestamp = time_interval(&resource->start_time, &cur_time);
		while (++idx < input->philo_num)
		{
			if (time_interval(&philo_data[idx].starve_start, &cur_time) >= input->time_to_die)
			{
				pthread_mutex_lock(&resource->mutex_die_checker);
				resource->die_cnt = DEAD;
				printf("%d %d%s", timestamp, philo_data[idx].pos, MSG_DIED);
				pthread_mutex_unlock(&resource->mutex_die_checker);
				break ;
			}
		}
		if (resource->die_cnt == DEAD)
			break ;
		usleep(5000);
	}
}

void	philo_begin(t_input *input, t_resource *resource, t_philo *philo_data)
{
	int	idx;

	gettimeofday(&resource->start_time, NULL);
	idx = -1;
	while (++idx < input->philo_num)
		philo_data[idx].starve_start = resource->start_time;
	idx = -1;
	while (++idx < input->philo_num)
		pthread_create(&philo_data[idx].self, NULL, survive, &philo_data[idx]);
	death_monitor(input, resource, philo_data);
	idx = -1;
	while (++idx < input->philo_num)
		pthread_join(philo_data[idx].self, NULL);
}

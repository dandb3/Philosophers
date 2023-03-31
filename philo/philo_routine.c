#include "philo.h"

static int	take_forks(t_philo *philo_data)
{
	pthread_mutex_lock(philo_data->first_fork);
	if (print_msg(philo_data, MSG_FORK, MODE_FORK) == RET_FAILURE)
	{
		pthread_mutex_unlock(philo_data->first_fork);
		return (RET_FAILURE);
	}
	pthread_mutex_lock(philo_data->second_fork);
	if (print_msg(philo_data, MSG_FORK, MODE_FORK) == RET_FAILURE)
	{
		pthread_mutex_unlock(philo_data->first_fork);
		pthread_mutex_unlock(philo_data->second_fork);
		return (RET_FAILURE);
	}
	return (RET_SUCCESS);
}

static int	philo_eat(t_philo *philo_data)
{
	if (take_forks(philo_data) == RET_FAILURE)
		return (RET_FAILURE);
	if (print_msg(philo_data, MSG_EAT, MODE_EAT) == RET_FAILURE)
	{
		pthread_mutex_unlock(philo_data->first_fork);
		pthread_mutex_unlock(philo_data->second_fork);
		return (RET_FAILURE);
	}
	usleep(philo_data->input->time_to_eat * 1000);
	pthread_mutex_unlock(philo_data->first_fork);
	pthread_mutex_unlock(philo_data->second_fork);
	return (RET_SUCCESS);
}

static int	philo_sleep(t_philo *philo_data)
{
	if (print_msg(philo_data, MSG_SLEEP, MODE_SLEEP) == RET_FAILURE)
		return (RET_FAILURE);
	usleep(philo_data->input->time_to_sleep * 1000);
	return (RET_SUCCESS);
}

static int	philo_think(t_philo *philo_data)
{
	return (print_msg(philo_data, MSG_THINK, MODE_THINK));
}

void	*routine(t_philo *philo_data)
{
	while (1)
	{
		if (philo_eat(philo_data) == RET_FAILURE)
			return ((void *)RET_FAILURE);
		if (philo_sleep(philo_data) == RET_FAILURE)
			return ((void *)RET_FAILURE);
		if (philo_think(philo_data) == RET_FAILURE)
			return ((void *)RET_FAILURE);
	}
	return ((void *)RET_SUCCESS);
}

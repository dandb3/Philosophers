/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_busy_wait.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:33:51 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/08 10:13:49 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	end_check(t_philo *philo_data)
{
	pthread_mutex_lock(&philo_data->resource->mutex_simul);
	if (philo_data->resource->simul_status == DEAD_OR_FULL)
	{
		pthread_mutex_unlock(&philo_data->resource->mutex_simul);
		return (RET_FAILURE);
	}
	pthread_mutex_unlock(&philo_data->resource->mutex_simul);
	if (time_interval(&philo_data->last_eat, &philo_data->cur_time)
		>= philo_data->input->time_to_die)
	{
		print_msg(philo_data, MSG_DIED, MODE_DIED);
		return (RET_FAILURE);
	}
	return (RET_SUCCESS);
}

int	busy_wait(t_philo *philo_data, t_milisec duration)
{
	gettimeofday(&philo_data->wait_start, NULL);
	while (1)
	{
		usleep(300);
		gettimeofday(&philo_data->cur_time, NULL);
		if (end_check(philo_data) == RET_FAILURE)
			return (RET_FAILURE);
		if (time_interval(&philo_data->wait_start, &philo_data->cur_time) \
			>= duration)
			return (RET_SUCCESS);
	}
}

static int	check_fork(t_philo *philo_data, pthread_mutex_t *mutex_fork, \
	t_status *fork_status)
{
	unsigned int	wait_interval;

	wait_interval = 300;
	while (1)
	{
		gettimeofday(&philo_data->cur_time, NULL);
		if (end_check(philo_data) == RET_FAILURE)
			return (RET_FAILURE);
		pthread_mutex_lock(mutex_fork);
		if (*fork_status == PICK_UP)
		{
			pthread_mutex_unlock(mutex_fork);
			usleep(wait_interval);
			if (wait_interval > 50)
				wait_interval -= 5;
			continue ;
		}
		*fork_status = PICK_UP;
		pthread_mutex_unlock(mutex_fork);
		print_msg(philo_data, MSG_FORK, MODE_FORK);
		return (RET_SUCCESS);
	}
}

int	hold_forks(t_philo *philo_data)
{
	if (check_fork(philo_data, philo_data->forks.first,
			philo_data->forks.first_status) == RET_FAILURE)
		return (RET_FAILURE);
	if (check_fork(philo_data, philo_data->forks.second,
			philo_data->forks.second_status) == RET_FAILURE)
		return (RET_FAILURE);
	return (RET_SUCCESS);
}

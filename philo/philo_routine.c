/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:03:35 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/02 14:08:39 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo_data)
{
	pthread_mutex_lock(philo_data->first_fork);
	if (print_msg(philo_data, MSG_FORK) == RET_FAILURE)
	{
		pthread_mutex_unlock(philo_data->first_fork);
		return (RET_FAILURE);
	}
	pthread_mutex_lock(philo_data->second_fork);
	if (print_msg(philo_data, MSG_FORK) == RET_FAILURE)
	{
		pthread_mutex_unlock(philo_data->first_fork);
		pthread_mutex_unlock(philo_data->second_fork);
		return (RET_FAILURE);
	}
	return (RET_SUCCESS);
}

static int	philo_eat(t_philo *philo_data)
{
	struct timeval	before_wait;
	struct timeval	after_wait;

	usleep(100);
	if (take_forks(philo_data) == RET_FAILURE)
		return (RET_FAILURE);
	if (print_msg_eat(philo_data, MSG_EAT) == RET_FAILURE)
	{
		pthread_mutex_unlock(philo_data->first_fork);
		pthread_mutex_unlock(philo_data->second_fork);
		return (RET_FAILURE);
	}
	gettimeofday(&before_wait, NULL);
	usleep(philo_data->input->time_to_eat * 800);
	gettimeofday(&after_wait, NULL);
	pseudo_spinlock(&after_wait, philo_data->input->time_to_eat
		- time_interval(&before_wait, &after_wait));
	pthread_mutex_unlock(philo_data->first_fork);
	pthread_mutex_unlock(philo_data->second_fork);
	return (RET_SUCCESS);
}

static int	philo_sleep(t_philo *philo_data)
{
	struct timeval	before_wait;
	struct timeval	after_wait;

	if (print_msg(philo_data, MSG_SLEEP) == RET_FAILURE)
		return (RET_FAILURE);
	gettimeofday(&before_wait, NULL);
	usleep(philo_data->input->time_to_sleep * 800);
	gettimeofday(&after_wait, NULL);
	pseudo_spinlock(&after_wait, philo_data->input->time_to_sleep
		- time_interval(&before_wait, &after_wait));
	return (RET_SUCCESS);
}

static int	philo_think(t_philo *philo_data)
{
	return (print_msg(philo_data, MSG_THINK));
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

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

static void	drop_forks(t_philo *philo_data)
{
	pthread_mutex_lock(philo_data->forks.first);
	philo_data->forks.first_status = PUT_DOWN;
	pthread_mutex_unlock(philo_data->forks.first);
	pthread_mutex_lock(philo_data->forks.second);
	philo_data->forks.second_status = PUT_DOWN;
	pthread_mutex_unlock(philo_data->forks.second);
}

static int	philo_eat(t_philo *philo_data)
{
	usleep(100);
	if (hold_forks(philo_data) == RET_FAILURE)
		return (RET_FAILURE);
	if (print_msg(philo_data, MSG_EAT, MODE_EAT) == RET_FAILURE)
		return (RET_FAILURE);
	if (busy_wait(philo_data, philo_data->input->time_to_eat)
		== RET_FAILURE)
		return (RET_FAILURE);
	drop_forks(philo_data);
	return (RET_SUCCESS);
}

static int	philo_sleep(t_philo *philo_data)
{
	if (print_msg(philo_data, MSG_SLEEP, MODE_SLEEP) == RET_FAILURE)
		return (RET_FAILURE);
	if (busy_wait(philo_data, philo_data->input->time_to_sleep)
		== RET_FAILURE)
		return (RET_FAILURE);
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

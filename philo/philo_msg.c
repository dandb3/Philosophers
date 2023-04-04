/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:03:27 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/01 20:32:18 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	full_check(t_philo *philo_data)
{
	int	full_flag;

	full_flag = 0;
	if (++(philo_data->eat_cnt) == philo_data->input->number_of_times)
	{
		pthread_mutex_lock(&philo_data->resource->mutex_full);
		if (++(philo_data->resource->full_cnt) == philo_data->input->philo_num)
			full_flag = 1;
		pthread_mutex_unlock(&philo_data->resource->mutex_full);
		if (full_flag)
		{
			pthread_mutex_lock(&philo_data->resource->mutex_simul);
			philo_data->resource->simul_status = DEAD_OR_FULL;
			pthread_mutex_unlock(&philo_data->resource->mutex_simul);
			return (RET_FAILURE);
		}
	}
	return (RET_SUCCESS);
}

int	print_msg(t_philo *philo_data, const char *msg, t_mode mode)
{
	struct timeval	cur_time;
	t_milisec		timestamp;

	gettimeofday(&cur_time, NULL);
	timestamp = time_interval(&philo_data->resource->start_time, &cur_time);
	pthread_mutex_lock(&philo_data->resource->mutex_simul);
	if (philo_data->resource->simul_status == DEAD_OR_FULL)
	{
		pthread_mutex_unlock(&philo_data->resource->mutex_simul);
		return (RET_FAILURE);
	}
	printf("%d %d%s", timestamp, philo_data->pos, msg);
	pthread_mutex_unlock(&philo_data->resource->mutex_simul);
	if (mode == MODE_EAT)
	{
		philo_data->last_eat = cur_time;
		if (full_check(philo_data) == RET_FAILURE)
			return (RET_FAILURE);
	}
	return (RET_SUCCESS);
}

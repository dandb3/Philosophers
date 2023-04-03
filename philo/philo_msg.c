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

static void	full_check(t_philo *philo_data)
{
	if (++(philo_data->eat_cnt) == philo_data->input->number_of_times)
	{
		pthread_mutex_lock(&philo_data->resource->mutex_simul);
		if (++(philo_data->resource->simul_status)
			== philo_data->input->philo_num)
			philo_data->resource->simul_status = DEAD_OR_FULL;
		pthread_mutex_unlock(&philo_data->resource->mutex_simul);
	}
}

int	print_msg(t_philo *philo_data, const char *msg, t_mode mode)
{
	struct timeval	cur_time;
	t_milisec		timestamp;

	gettimeofday(&cur_time, NULL);
	timestamp = time_interval(&philo_data->resource->start_time, &cur_time);
	if (mode == MODE_EAT)
	{
		philo_data->last_eat = cur_time;
		full_check(philo_data);
	}
	pthread_mutex_lock(&philo_data->resource->mutex_simul);
	if (philo_data->resource->simul_status == DEAD_OR_FULL)
	{
		pthread_mutex_unlock(&philo_data->resource->mutex_simul);
		return (RET_FAILURE);
	}
	printf("%d %d%s", timestamp, philo_data->pos, msg);
	pthread_mutex_unlock(&philo_data->resource->mutex_simul);
	return (RET_SUCCESS);
}

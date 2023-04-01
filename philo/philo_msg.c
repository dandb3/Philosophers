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

int	print_msg(t_philo *philo_data, const char *msg)
{
	struct timeval	cur_time;
	t_milisec		timestamp;

	gettimeofday(&cur_time, NULL);
	timestamp = time_interval(philo_data->survive_start, &cur_time);
	pthread_mutex_lock(philo_data->mutex_die_checker);
	if (*philo_data->die_cnt == DEAD_OR_FULL)
	{
		pthread_mutex_unlock(philo_data->mutex_die_checker);
		return (RET_FAILURE);
	}
	printf("%d %d%s", timestamp, philo_data->pos, msg);
	pthread_mutex_unlock(philo_data->mutex_die_checker);
	return (RET_SUCCESS);
}

int	print_msg_eat(t_philo *philo_data, const char *msg)
{
	t_milisec		timestamp;
	int				philo_full;

	philo_full = 0;
	gettimeofday(&philo_data->starve_start, NULL);
	timestamp
		= time_interval(philo_data->survive_start, &philo_data->starve_start);
	if (++(philo_data->eat_cnt) == philo_data->input->number_of_times)
		philo_full = 1;
	pthread_mutex_lock(philo_data->mutex_die_checker);
	if (*philo_data->die_cnt == DEAD_OR_FULL)
	{
		pthread_mutex_unlock(philo_data->mutex_die_checker);
		return (RET_FAILURE);
	}
	printf("%d %d%s", timestamp, philo_data->pos, msg);
	if (philo_full && ++(*philo_data->die_cnt) == philo_data->input->philo_num)
		*philo_data->die_cnt = DEAD_OR_FULL;
	pthread_mutex_unlock(philo_data->mutex_die_checker);
	return (RET_SUCCESS);
}

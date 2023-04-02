/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:59:40 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/02 14:28:34 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*survive(void *philo)
{
	t_philo	*philo_data;

	philo_data = (t_philo *) philo;
	print_msg(philo_data, MSG_THINK);
	if (philo_data->input->philo_num == 1)
	{
		print_msg(philo_data, MSG_FORK);
		return ((void *)RET_SUCCESS);
	}
	if (philo_data->pos % 2 == 0)
		usleep(philo_data->input->time_to_eat * 500);
	return (routine(philo_data));
}

static int	full_check(t_resource *resource)
{
	if (resource->die_cnt == DEAD_OR_FULL)
	{
		pthread_mutex_unlock(&resource->mutex_die_checker);
		return (RET_FAILURE);
	}
	return (RET_SUCCESS);
}

static void	death_monitor(t_input *input,
	t_resource *resource, t_philo *philo_data)
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
			if (time_interval(&philo_data[idx].starve_start, &cur_time)
				>= input->time_to_die)
			{
				pthread_mutex_lock(&resource->mutex_die_checker);
				if (full_check(resource) == RET_FAILURE)
					return ;
				resource->die_cnt = DEAD_OR_FULL;
				printf("%d %d%s", timestamp, philo_data[idx].pos, MSG_DIED);
				pthread_mutex_unlock(&resource->mutex_die_checker);
				return ;
			}
		}
		usleep(1000);
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

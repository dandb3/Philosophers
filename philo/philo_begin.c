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
	print_msg(philo_data, MSG_THINK, MODE_THINK);
	if (philo_data->input->philo_num == 1)
	{
		print_msg(philo_data, MSG_FORK, MODE_FORK);
		return ((void *)RET_SUCCESS);
	}
	if (philo_data->pos % 2 == 0)
		usleep(philo_data->input->time_to_eat * 500);
	return (routine(philo_data));
}

void	philo_begin(t_input *input, t_resource *resource, t_philo *philo_data)
{
	int	idx;

	gettimeofday(&resource->start_time, NULL);
	idx = -1;
	while (++idx < input->philo_num)
		philo_data[idx].last_eat = resource->start_time;
	idx = -1;
	while (++idx < input->philo_num)
		pthread_create(&philo_data[idx].self, NULL, survive, &philo_data[idx]);
	idx = -1;
	while (++idx < input->philo_num)
		pthread_join(philo_data[idx].self, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:02:25 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/01 15:15:32 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_resource(t_resource *resource, t_input *input)
{
	int	idx;

	idx = -1;
	while (++idx < input->philo_num)
		pthread_mutex_destroy(&resource->mutex_forks[idx]);
	pthread_mutex_destroy(&resource->mutex_simul);
	pthread_mutex_destroy(&resource->mutex_full);
	free(resource->mutex_forks);
	free(resource->forks_status);
}

void	free_all_data(t_input *input, t_resource *resource, t_philo *philo_data)
{
	free(philo_data);
	free_resource(resource, input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:51:21 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/28 16:56:27 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_tables(t_info *info, t_resource *resource)
{
	int	idx;

	resource->philosophers = (pthread_t *) malloc(sizeof(pthread_t)
			* info->number_of_philosophers);
	if (resource->philosophers == NULL)
		return (error_malloc());
	resource->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* info->number_of_philosophers);
	if (resource->forks == NULL)
		return (free_and_ret(resource->philosophers,
				NULL, NULL, error_malloc()));
	idx = -1;
	while (++idx < info->number_of_philosophers)
	{
		if (pthread_mutex_init(&resource->forks[idx], NULL) == RET_FAILURE)
		{
			destroy_mutex_until(resource->forks, idx);
			return (free_and_ret(resource->philosophers,
					NULL, NULL, error_mutex_init()));
		}
	}
	resource->monitor = 0;
	return (RET_SUCCESS);
}

static int	set_philosophers(t_info *info, t_resource *resource,
	t_philo *philosophers)
{
	struct timeval	start_time;
	int				idx;

	philosophers
		= (t_philo *) malloc(sizeof(t_philo) * info->number_of_philosophers);
	if (philosophers == NULL)
		return (error_malloc());
	idx = -1;
	while (++idx < info->number_of_philosophers)
	{
		philosophers[idx].monitor_mutex = &resource->monitor_mutex;
		philosophers[idx].info = info;
		philosophers[idx].monitor = &resource->monitor;
		philosophers[idx].idx = idx + 1;
		philosophers[idx].print_mutex = &resource->print_mutex;
		philosophers[idx].left_fork = &resource->forks[idx];
		philosophers[idx].right_fork
			= &resource->forks[(idx + 1) % info->number_of_philosophers];
	}
	if (gettimeofday(&start_time, NULL) == RET_FAILURE)
		return (free_and_ret(philosophers, NULL, NULL, error_gettime()));
	idx = -1;
	while (++idx < info->number_of_philosophers)
		philosophers[idx].last_time_eat = start_time;
	return (RET_SUCCESS);
}

int	philo_init(t_info *info, t_resource *resource, t_philo *philosophers)
{
	if (pthread_mutex_init(&resource->print_mutex, NULL) == RET_FAILURE)
		return (error_mutex_init());
	if (pthread_mutex_init(&resource->monitor_mutex, NULL) == RET_FAILURE)
	{
		pthread_mutex_destroy(&resource->print_mutex);
		return (error_mutex_init());
	}
	if (set_tables(info, resource) == RET_FAILURE)
	{
		pthread_mutex_destroy(&resource->print_mutex);
		pthread_mutex_destroy(&resource->monitor_mutex);
		return (RET_FAILURE);
	}
	if (set_philosophers(info, resource, philosophers) == RET_FAILURE)
	{
		destroy_mutex_until(resource->forks, info->number_of_philosophers);
		pthread_mutex_destroy(&resource->print_mutex);
		pthread_mutex_destroy(&resource->monitor_mutex);
		return (free_and_ret(resource->philosophers, NULL, NULL, RET_FAILURE));
	}
	return (RET_SUCCESS);
}

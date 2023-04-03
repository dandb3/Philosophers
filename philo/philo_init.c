/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:02:28 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/01 20:33:14 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	input_init(t_input *input, char *argv[])
{
	input->philo_num = philo_atoi(argv[1]);
	input->time_to_die = philo_atoi(argv[2]);
	input->time_to_eat = philo_atoi(argv[3]);
	input->time_to_sleep = philo_atoi(argv[4]);
	input->number_of_times = 0;
	if (argv[5] != NULL)
		input->number_of_times = philo_atoi(argv[5]);
	if (input->philo_num == RET_FAILURE || input->time_to_die == RET_FAILURE
		|| input->time_to_eat == RET_FAILURE
		|| input->time_to_sleep == RET_FAILURE
		|| (argv[5] != NULL && input->number_of_times == RET_FAILURE))
		return (RET_FAILURE);
	return (RET_SUCCESS);
}

static int	resource_init(t_input *input, t_resource *resource)
{
	int	idx;

	resource->mutex_forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * input->philo_num);
	if (resource->mutex_forks == NULL)
		return (RET_FAILURE);
	resource->forks_status = (int *) malloc(sizeof(int) * input->philo_num);
	if (resource->forks_status == NULL)
	{
		free(resource->mutex_forks);
		return (RET_FAILURE);
	}
	memset(resource->forks_status, PUT_DOWN, sizeof(int) * input->philo_num);
	idx = -1;
	while (++idx < input->philo_num)
		pthread_mutex_init(&resource->mutex_forks[idx], NULL);
	pthread_mutex_init(&resource->mutex_simul, NULL);
	resource->simul_status = 0;
	return (RET_SUCCESS);
}

static void	philo_fork_init(t_input *input, t_resource *resource,
	t_philo **philo_data, int idx)
{
	if ((idx + 1) % 2 == 1)
	{
		(*philo_data)[idx].forks.first = &resource->mutex_forks[idx];
		(*philo_data)[idx].forks.second
			= &resource->mutex_forks[(idx + 1) % input->philo_num];
		(*philo_data)[idx].forks.first_status = &resource->forks_status[idx];
		(*philo_data)[idx].forks.second_status
			= &resource->forks_status[(idx + 1) % input->philo_num];
	}
	else
	{
		(*philo_data)[idx].forks.second = &resource->mutex_forks[idx];
		(*philo_data)[idx].forks.first
			= &resource->mutex_forks[(idx + 1) % input->philo_num];
		(*philo_data)[idx].forks.second_status = &resource->forks_status[idx];
		(*philo_data)[idx].forks.first_status
			= &resource->forks_status[(idx + 1) % input->philo_num];
	}
}

static int	philo_data_init(t_input *input,
	t_resource *resource, t_philo **philo_data)
{
	int	idx;

	*philo_data = (t_philo *) malloc(sizeof(t_philo) * input->philo_num);
	if (*philo_data == NULL)
		return (RET_FAILURE);
	idx = -1;
	while (++idx < input->philo_num)
	{
		philo_fork_init(input, resource, philo_data, idx);
		(*philo_data)[idx].resource = resource;
		(*philo_data)[idx].pos = idx + 1;
		(*philo_data)[idx].input = input;
		(*philo_data)[idx].eat_cnt = 0;
	}
	return (RET_SUCCESS);
}

int	philo_init(t_input *input, t_resource *resource,
	t_philo **philo_data, char *argv[])
{
	if (input_init(input, argv) == RET_FAILURE)
	{
		error_msg(ERR_INPUT);
		return (RET_FAILURE);
	}
	if (resource_init(input, resource) == RET_FAILURE)
	{
		error_msg(ERR_INIT);
		return (RET_FAILURE);
	}
	if (philo_data_init(input, resource, philo_data) == RET_FAILURE)
	{
		free_resource(resource, input);
		error_msg(ERR_INIT);
		return (RET_FAILURE);
	}
	return (RET_SUCCESS);
}

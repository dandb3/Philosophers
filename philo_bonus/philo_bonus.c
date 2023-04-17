/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:10:50 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/08 10:12:53 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	philo_init(t_info *info, t_input *input, t_resource *resource,
	char *argv[])
{
	if (input_init(input, argv) == RET_FAILURE)
	{
		error_msg(ERR_INPUT);
		return (RET_FAILURE);
	}
	if (info_init(info, input, resource) == RET_FAILURE)
	{
		error_msg(ERR_INIT);
		return (RET_FAILURE);
	}
	if (resource_init(input, resource) == RET_FAILURE)
	{
		error_msg(ERR_INIT);
		return (RET_FAILURE);
	}
	return (RET_SUCCESS);
}

static void	philo_begin(t_info *info)
{
	int	idx;

	idx = -1;
	gettimeofday(&info->start_time, NULL);
	info->last_eat = info->start_time;
	while (++idx < info->input->philo_num)
	{
		info->resource->pid_arr[idx] = fork();
		if (info->resource->pid_arr[idx] == 0)
		{
			info->pos = idx + 1;
			break ;
		}
	}
	if (idx < info->input->philo_num)
		philo_routine(info);
	else
		philo_manage(info);
}

int	philo(char *argv[])
{
	t_info		info;
	t_input		input;
	t_resource	resource;

	if (philo_init(&info, &input, &resource, argv) == RET_FAILURE)
		return (RET_FAILURE);
	philo_begin(&info);
	return (release_all(&info, RET_SUCCESS));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:11:14 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/08 10:11:15 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_sem_names(t_input *input, t_resource *resource, int ret)
{
	int	idx;

	idx = -1;
	while (++idx < input->philo_num)
		free(resource->sem_names[idx]);
	return (ret);
}

int	free_resource(t_resource *resource, int ret)
{
	free(resource->sem_names);
	free(resource->pid_arr);
	free(resource->sem_last_eat);
	return (ret);
}

int	free_all(t_input *input, t_resource *resource, int ret)
{
	free_sem_names(input, resource, ret);
	free_resource(resource, ret);
	return (ret);
}

int	release_all(t_info *info, int ret)
{
	unlink_all(info->input, info->resource, ret);
	free_sem_names(info->input, info->resource, ret);
	free_resource(info->resource, ret);
	return (ret);
}

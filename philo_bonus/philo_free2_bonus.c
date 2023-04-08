/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:11:17 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/08 10:11:18 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	unlink_sem_names(t_input *input, t_resource *resource, int ret)
{
	int	idx;

	idx = -1;
	while (++idx < input->philo_num)
		sem_unlink(resource->sem_names[idx]);
	return (ret);
}

int	unlink_semaphores(int ret)
{
	sem_unlink(SEM_FORKS_ACCESS);
	sem_unlink(SEM_FORKS_STATUS);
	sem_unlink(SEM_FULL_COUNTER);
	sem_unlink(SEM_PRINT);
	return (ret);
}

int	unlink_all(t_input *input, t_resource *resource, int ret)
{
	unlink_sem_names(input, resource, ret);
	unlink_semaphores(ret);
	return (ret);
}

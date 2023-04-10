/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:11:32 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/08 10:11:32 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_msg(t_info *info, const char *msg)
{
	sem_wait(info->resource->sem_print);
	gettimeofday(&info->cur_time, NULL);
	printf("%d %d%s", time_interval(&info->start_time, &info->cur_time), \
		info->pos, msg);
	sem_post(info->resource->sem_print);
}

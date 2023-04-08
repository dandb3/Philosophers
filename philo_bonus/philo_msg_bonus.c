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
	t_milisec		timestamp;

	timestamp = time_interval(&info->start_time, &info->cur_time);
	sem_wait(info->resource->sem_print);
	printf("%d %d%s", timestamp, info->pos, msg);
	sem_post(info->resource->sem_print);
}

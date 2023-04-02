/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pseudo_spinlock.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:33:51 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/02 14:09:54 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pseudo_spinlock(struct timeval *after_wait, t_milisec duration)
{
	struct timeval	cur_time;

	while (1)
	{
		usleep(300);
		gettimeofday(&cur_time, NULL);
		if (time_interval(after_wait, &cur_time) >= duration)
			return ;
	}
}

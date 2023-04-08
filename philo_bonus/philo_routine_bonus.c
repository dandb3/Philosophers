/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:11:40 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/08 10:11:41 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_eat(t_info *info)
{
	usleep(100);
	hold_forks(info);
	gettimeofday(&info->cur_time, NULL);
	sem_wait(info->resource->sem_last_eat[info->pos - 1]);
	info->last_eat = info->cur_time;
	sem_post(info->resource->sem_last_eat[info->pos - 1]);
	print_msg(info, MSG_EAT);
	if (++(info->eat_cnt) == info->input->number_of_times)
		sem_post(info->resource->full_counter);
	gettimeofday(&info->wait_start, NULL);
	usleep(info->input->time_to_eat * 800);
	busy_wait(info, info->input->time_to_eat);
	drop_forks(info);
}

static void	philo_sleep(t_info *info)
{
	gettimeofday(&info->cur_time, NULL);
	print_msg(info, MSG_SLEEP);
	gettimeofday(&info->wait_start, NULL);
	usleep(info->input->time_to_sleep * 800);
	busy_wait(info, info->input->time_to_sleep);
}

static void	philo_think(t_info *info)
{
	gettimeofday(&info->cur_time, NULL);
	print_msg(info, MSG_THINK);
}

static void	*death_monitor(void *void_info)
{
	struct timeval	cur_time;
	t_info			*info;
	t_milisec		survive_time;

	info = (t_info *) void_info;
	while (1)
	{
		usleep(300);
		gettimeofday(&cur_time, NULL);
		sem_wait(info->resource->sem_last_eat[info->pos - 1]);
		survive_time = time_interval(&info->last_eat, &cur_time);
		sem_post(info->resource->sem_last_eat[info->pos - 1]);
		if (survive_time >= info->input->time_to_die)
		{
			sem_wait(info->resource->sem_print);
			exit(1);
		}
	}
	return ((void *)RET_SUCCESS);
}

void	philo_routine(t_info *info)
{
	pthread_t	death_monitor_thread;

	pthread_create(&death_monitor_thread, NULL, death_monitor, info);
	pthread_detach(death_monitor_thread);
	while (1)
	{
		philo_think(info);
		philo_eat(info);
		philo_sleep(info);
	}
}

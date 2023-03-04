/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:50:55 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/28 17:16:35 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo_msg.h"

static void	print_msg(pthread_mutex_t *print_mutex, char const *str)
{
	pthread_mutex_lock(print_mutex);
	write(STDOUT_FILENO, str, ft_strlen(str));
	pthread_mutex_unlock(print_mutex);
}

static void	eat_even(t_philo *philo)
{
	if (philo->idx % 2 == 1)
		usleep(philo->info->time_to_eat * 500);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo->print_mutex, MSG_EAT);
		gettimeofday(&philo->last_time_eat, NULL);
		usleep(philo->info->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_msg(philo->print_mutex, MSG_SLEEP);
		usleep(philo->info->time_to_sleep * 1000);
		print_msg(philo->print_mutex, MSG_THINK);
	}
}

static void	*survive(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (philo->info->number_of_philosophers % 2 == 1)
		eat_odd();
	else
		eat_even();
}

int	begin_survival(t_info *info, t_resource *resource, t_philo *philosophers)
{
	int	idx;

	idx = -1;
	while (++idx < info->number_of_philosophers)
	{
		pthread_create(resource->philosophers[idx],
			NULL, survive, &philosophers[idx]);
	}
}

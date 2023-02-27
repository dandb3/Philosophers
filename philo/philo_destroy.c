/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:51:06 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/27 04:04:48 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_and_ret(void *freed1, void *freed2, void *freed3, int ret)
{
	free(freed1);
	free(freed2);
	free(freed3);
	return (ret);
}

/* destroy_ functions must be executed in main thread. */
void	destroy_mutex_until(pthread_mutex_t *forks, int cnt)
{
	int	idx;

	idx = -1;
	while (++idx < cnt)
		pthread_mutex_destroy(&forks[idx]);
	free(forks);
}

void	destroy_all(t_resource *resource, t_philo *philosophers, int ret)
{
	
}

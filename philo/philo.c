/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:03:45 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/01 14:03:45 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(char *argv[])
{
	t_input		input;
	t_resource	resource;
	t_philo		*philo_data;

	if (philo_init(&input, &resource, &philo_data, argv) == RET_FAILURE)
		return (RET_FAILURE);
	philo_begin(&input, &resource, philo_data);
	free_all_data(&input, &resource, philo_data);
	return (RET_SUCCESS);
}

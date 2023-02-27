/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:51:36 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/27 03:51:37 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(int argc, char *argv[])
{
	t_info			info;
	t_resource		resource;
	t_philo			*philosophers;

	if (input_info(&info, argc, argv) == RET_FAILURE)
		return (RET_FAILURE);
	if (philo_init(&info, &resource, philosophers) == RET_FAILURE)
		return (RET_FAILURE);
	if (begin_survival(&info, &resource, philosophers) == RET_FAILURE)
		return (RET_FAILURE);
	return (RET_SUCCESS);
}

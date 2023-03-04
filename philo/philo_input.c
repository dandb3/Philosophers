/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:51:24 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/28 17:03:03 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	atoi_range_check(char const *str)
{
	int	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '-')
		return (RET_FAILURE);
	if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		result = 10 * result + *str - '0';
		++str;
		if (result >= 1000)
			return (RET_FAILURE);
	}
	if (*str < '0' || *str > '9')
		return (RET_FAILURE);
	return (result);
}

int	input_info(t_info *info, int argc, char *argv[])
{
	info->number_of_philosophers = atoi_range_check(argv[1]);
	info->time_to_die = atoi_range_check(argv[2]);
	info->time_to_eat = atoi_range_check(argv[3]);
	info->time_to_sleep = atoi_range_check(argv[4]);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat
			= atoi_range_check(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = 0;
	if ((info->number_of_philosophers | info->time_to_die \
		| info->time_to_eat | info->time_to_sleep \
		| info->number_of_times_each_philosopher_must_eat) == RET_FAILURE)
		return (error_input());
	return (RET_SUCCESS);
}

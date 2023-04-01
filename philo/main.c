/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:59:45 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/01 15:15:29 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		error_msg(ERR_INPUT);
		return (EXIT_FAILURE);
	}
	if (philo(argv) == RET_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

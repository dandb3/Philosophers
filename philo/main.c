/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:50:47 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/27 03:50:51 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (error_argc());
	if (philo(argc, argv) == RET_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

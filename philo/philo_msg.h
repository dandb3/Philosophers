/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:51:29 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/27 03:51:30 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_MSG_H
# define PHILO_MSG_H

# define ERR_INPUT "Please put arguments correctly :\n \
						number_of_philosophers time_to_die \
						time_to_eat time_to_sleep \
						[number_of_times_each_philosopher_must_eat]\n"
# define ERR_NUM "Please put positive integer value smaller than 1000000.\n"
# define ERR_MUTEX "Mutex initialization error\n"
# define ERR_MALLOC "Malloc error\n"
# define ERR_GETTIME "Gettimeofday error\n"
# define MSG_FORK " has taken a fork\n"
# define MSG_EAT " is eating\n"
# define MSG_SLEEP " is sleeping\n"
# define MSG_THINK " is thinking\n"
# define MSG_DIED " died\n"

#endif
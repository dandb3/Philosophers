/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:03:48 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/02 14:03:10 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "philo_msg.h"
# include "philo_error.h"

# define RET_SUCCESS 0
# define RET_FAILURE -1
# define DEAD_OR_FULL -1

typedef int	t_milisec;
typedef enum e_status
{
	PUT_DOWN = 0,
	PICK_UP
}	t_status;
typedef enum e_mode
{
	MODE_EAT,
	MODE_THINK,
	MODE_SLEEP,
	MODE_FORK,
	MODE_DIED
}	t_mode;

typedef struct s_input
{
	t_milisec	time_to_die;
	t_milisec	time_to_eat;
	t_milisec	time_to_sleep;
	int			number_of_times;
	int			philo_num;
}	t_input;

typedef struct s_forks
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	t_status		*first_status;
	t_status		*second_status;
}	t_forks;

typedef struct s_resource
{
	struct timeval	start_time;
	pthread_mutex_t	mutex_simul;
	pthread_mutex_t	*mutex_forks;
	t_status		*forks_status;
	int				simul_status;
}	t_resource;

typedef struct s_philo
{
	t_forks			forks;
	struct timeval	last_eat;
	struct timeval	wait_start;
	pthread_t		self;
	t_resource		*resource;
	t_input			*input;
	int				eat_cnt;
	int				pos;
}	t_philo;

/* start */
int			philo(char *argv[]);
void		philo_begin(t_input *input, t_resource *resource,
				t_philo *philo_data);
void		*routine(t_philo *philo_data);
int			busy_wait(t_philo *philo_data, t_milisec duration);
int			hold_forks(t_philo *philo_data);

/* print */
int			print_msg(t_philo *philo_data, const char *msg, t_mode mode);

/* initialize */
int			philo_init(t_input *input, t_resource *resource,
				t_philo **philo_data, char *argv[]);

/* free */
void		free_resource(t_resource *resource, t_input *input);
void		free_all_data(t_input *input, t_resource *resource,
				t_philo *philo_data);

/* utilities */
size_t		ft_strlen(const char *str);
t_milisec	time_interval(struct timeval *start_time, struct timeval *cur_time);
int			philo_atoi(const char *str);

#endif

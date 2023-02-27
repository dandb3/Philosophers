/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:51:40 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/27 04:00:17 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef int t_milisec;

typedef struct s_info
{
	int			number_of_philosophers;
	t_milisec	time_to_die;
	t_milisec	time_to_eat;
	t_milisec	time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
}	t_info;

typedef struct s_resource
{
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_resource;

typedef struct s_philo
{
	struct timeval	last_time_eat;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				idx;
}	t_philo;

enum e_ret_stat
{
	RET_FAILURE = -1,
	RET_SUCCESS
};

int			philo(int argc, char *argv[]);
int			philo_died(t_philo *philosophers, t_info *philo_info);

/* ---------------------- initialize ----------------------- */
int			input_info(t_info *info, int argc, char *argv[]);
int			philo_init(t_info *info, t_resource *resource, t_philo *philosophers);

/* ------------------------- utils ------------------------- */
size_t		ft_strlen(const char *str);
t_milisec	starve_time(struct timeval *start_time, struct timeval *cur_time);

/* ------------------------ destroy ------------------------ */
int			free_and_ret(void *freed1, void *freed2, void *freed3, int ret);
void		destroy_mutex_until(pthread_mutex_t *forks, int cnt);

/* ----------------------- error_msg ----------------------- */
int			error_argc(void);
int			error_input(void);
int			error_malloc(void);
int			error_mutex_init(void);
int			error_gettime(void);

#endif

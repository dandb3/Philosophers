#ifndef PHILO_BOUNS_H
# define PHILO_BOUNS_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "philo_msg_bonus.h"
# include "philo_error_bonus.h"

# define RET_SUCCESS 0
# define RET_FAILURE -1
# define DELAY 50
# define DEAD_OR_FULL 1

typedef int t_milisec;
typedef enum e_mode
{
	MODE_EAT,
	MODE_SLEEP,
	MODE_THINK,
	MODE_FORK
}	t_mode;

typedef struct s_input
{
	t_milisec	time_to_die;
	t_milisec	time_to_eat;
	t_milisec	time_to_sleep;
	int			number_of_times;
	int			philo_num;
}	t_input;

typedef struct s_philo
{
	struct timeval	starve_start;
	pthread_t		self;
	struct timeval	*survive_start;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	*mutex_die_checker;
	t_input			*input;
	int				*die_cnt;
	int				pos;
}	t_philo;

typedef struct s_resource
{
	struct timeval	start_time;
	pthread_mutex_t	mutex_die_checker;
	pthread_mutex_t	*forks;
	int				die_cnt;
}	t_resource;

#endif
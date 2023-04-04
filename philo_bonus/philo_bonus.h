#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/wait.h>
# include "philo_msg_bonus.h"
# include "philo_error_bonus.h"

# define SEM_FORKS_STATUS "/forks_status"
# define SEM_FORKS_ACCESS "/forks_access"
# define SEM_FULL_COUNTER "/full_counter"
# define RET_SUCCESS 0
# define RET_FAILURE -1

typedef int t_milisec;

typedef struct s_input
{
	t_milisec	time_to_die;
	t_milisec	time_to_eat;
	t_milisec	time_to_sleep;
	int			number_of_times;
	int			philo_num;
}	t_input;

typedef struct s_resource
{
	sem_t	*forks_status;
	sem_t	*forks_access;
	sem_t	*full_counter;
}	t_resource;

typedef struct s_info
{
	struct timeval	start_time;
	struct timeval	last_eat;
	struct timeval	wait_start;
	t_input 		*input;
	t_resource 		*resource;
	pid_t			*pid_arr;
}	t_info;


/* start */
void		philo_begin(t_info *info);
int			philo(char *argv[]);

/* procedure */
void		philo_manage(t_info *info);
void		philo_routine(t_info *info);

/* utilities */
size_t		ft_strlen(const char *str);
t_milisec	time_interval(struct timeval *start_time, struct timeval *cur_time);
int			philo_atoi(const char *str);

/* initialize */
int			philo_init(t_info *info, t_input *input, t_resource *resource,
				char *argv[]);

/* free */
void		free_resource(void);
void		free_all_data(pid_t *pid_arr);

#endif

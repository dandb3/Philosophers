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

# define SEM_FORKS_STATUS "/sem_forks_status"
# define SEM_FORKS_ACCESS "/sem_forks_access"
# define SEM_FULL_COUNTER "/sem_full_counter"
# define SEM_PRINT "/sem_print"
# define RET_SUCCESS 0
# define RET_FAILURE -1
# define DEAD 1
# define ALIVE 0
# define USING 1
# define AVAILABLE 0

typedef int t_milisec;
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

typedef struct s_resource
{
	sem_t	*forks_status;
	sem_t	*forks_access;
	sem_t	*full_counter;
	sem_t	*sem_print;
	int		status;
}	t_resource;

typedef struct s_info
{
	struct timeval	start_time;
	struct timeval	last_eat;
	struct timeval	wait_start;
	t_input 		*input;
	t_resource 		*resource;
	pid_t			*pid_arr;
	int				eat_cnt;
	int				pos;
}	t_info;

void	print_msg(t_info *info, const char *msg, t_mode mode);
void	hold_forks(t_info *info);
void	busy_wait(t_info *info, t_milisec duration);

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

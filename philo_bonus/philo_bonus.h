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
# define SEM_LAST_EAT "/sem_last_eat_"
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
	sem_t	*sem_print;
	sem_t	**sem_last_eat;
	char	**sem_names;
	pid_t	*pid_arr;
}	t_resource;

typedef struct s_info
{
	struct timeval	start_time;
	struct timeval	last_eat;
	struct timeval	wait_start;
	struct timeval	cur_time;
	t_input 		*input;
	t_resource 		*resource;
	int				eat_cnt;
	int				pos;
}	t_info;

/* start */
int			philo(char *argv[]);

/* procedure */
void		philo_manage(t_info *info);
void		philo_routine(t_info *info);

/* small_procedure */
void		print_msg(t_info *info, const char *msg);
void		busy_wait(t_info *info, t_milisec duration);
void		hold_forks(t_info *info);
void		drop_forks(t_info *info);

/* utilities */
size_t		ft_strlen(const char *str);
t_milisec	time_interval(struct timeval *start_time, struct timeval *cur_time);
int			philo_atoi(const char *str);
char		*small_itoa(int num);
char		*strjoin_and_free(char *s1, char *s2);

/* initialize */
int			input_init(t_input *input, char *argv[]);
int			info_init(t_info *info, t_input *input, t_resource *resource);
int			resource_init(t_input *input, t_resource *resource);

/* free */
int			unlink_sem_names(t_input *input, t_resource *resource, int ret);
int			unlink_semaphores(int ret);
int			unlink_all(t_input *input, t_resource *resource, int ret);
int			free_sem_names(t_input *input, t_resource *resource, int ret);
int			free_resource(t_resource *resource, int ret);
int			free_all(t_input *input, t_resource *resource, int ret);
int			release_all(t_info *info, int ret);

#endif

#ifndef PHILO_MSG_H
# define PHILO_MSG_H

# define MSG_FORK " has taken a fork\n"
# define MSG_EAT " is eating\n"
# define MSG_SLEEP " is sleeping\n"
# define MSG_THINK " is thinking\n"
# define MSG_DIED " died\n"

# include <pthread.h>

int	check_die_msg(pthread_mutex_t *mutex_die_checker);

#endif
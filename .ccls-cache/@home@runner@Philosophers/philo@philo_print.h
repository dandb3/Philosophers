#ifndef PHILO_PRINT_H
# define PHILO_PRINT_H

# include <unistd.h>

# define MSG_INPUT_ERR "Please put arguments correctly :\n \
						number_of_philosophers time_to_die \
						time_to_eat time_to_sleep \
						[number_of_times_each_philosopher_must_eat]\n"
# define MSG_NUM_ERR "Please put positive integer value smaller than 1000000.\n"
# define MSG_FORK " has taken a fork\n"
# define MSG_EAT " is eating\n"
# define MSG_SLEEP " is sleeping\n"
# define MSG_THINK " is thinking\n"
# define MSG_DIED " died\n"

/* ----------------------- error_msg ----------------------- */
int	error_argc(void);
int	error_input(void);

/* ----------------------- print_msg ----------------------- */

#endif
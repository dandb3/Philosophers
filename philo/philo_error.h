#ifndef PHILO_ERROR_H
# define PHILO_ERROR_H

# define ERR_INPUT "Invalid input: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (number_of_times_each_philosopher_must_eat)\n"
# define ERR_INIT "Initialization Failed\n"

void	error_msg(const char *msg);

#endif
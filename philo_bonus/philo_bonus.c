#include "philo_bonus.h"

int	philo(char *argv[])
{
	t_info		info;
	t_input 	input;
	t_resource	resource;

	if (philo_init(&info, &input, &resource, argv) == RET_FAILURE)
		return (RET_FAILURE);
	philo_begin(&info);
	free_all_data(info.pid_arr);
	return (RET_SUCCESS);
}

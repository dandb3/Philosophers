#include "philo.h"

int	philo(char *argv[])
{
	t_input		input;
	t_resource	resource;
	t_philo		*philo_data;

	if (philo_init(&input, &resource, &philo_data, argv) == RET_FAILURE)
		return (RET_FAILURE);
	philo_begin(&input, &resource, philo_data);
	free_all_data(&input, &resource, philo_data);
	return (RET_SUCCESS);
}

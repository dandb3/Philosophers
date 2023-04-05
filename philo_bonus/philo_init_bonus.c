#include "philo_bonus.h"

int	input_init(t_input *input, char *argv[])
{
	input->philo_num = philo_atoi(argv[1]);
	input->time_to_die = philo_atoi(argv[2]);
	input->time_to_eat = philo_atoi(argv[3]);
	input->time_to_sleep = philo_atoi(argv[4]);
	input->number_of_times = 0;
	if (argv[5] != NULL)
		input->number_of_times = philo_atoi(argv[5]);
	if (input->philo_num == RET_FAILURE || input->time_to_die == RET_FAILURE
		|| input->time_to_eat == RET_FAILURE
		|| input->time_to_sleep == RET_FAILURE
		|| input->number_of_times == RET_FAILURE)
		return (RET_FAILURE);
	return (RET_SUCCESS);
}

int	info_init(t_info *info, t_input *input, t_resource *resource)
{
	info->input = input;
	info->resource = resource;
	info->eat_cnt = 0;
	return (RET_SUCCESS);
}

static int	malloc_all(t_input *input, t_resource *resource)
{
	int	idx;

	resource->pid_arr = (pid_t *) malloc(sizeof(pid_t) * input->philo_num);
	resource->sem_last_eat
		= (sem_t **) malloc(sizeof(sem_t *) * input->philo_num);
	resource->sem_names = (char **) malloc(sizeof(char *) * input->philo_num);
	if (resource->pid_arr == NULL || resource->sem_last_eat == NULL
		|| resource->sem_names == NULL)
		return (free_resource(resource, RET_FAILURE));
	idx = -1;
	while (++idx < input->philo_num)
		resource->sem_names[idx]
			= strjoin_and_free(SEM_LAST_EAT, small_itoa(idx + 1));
	idx = -1;
	while (++idx < input->philo_num)
		if (resource->sem_names[idx] == NULL)
			return (free_all(input, resource, RET_FAILURE));
	return (RET_SUCCESS);
}

static int	make_semaphores(t_input *input, t_resource *resource)
{
	int	idx;

	resource->forks_status = sem_open(SEM_FORKS_STATUS, O_CREAT,
		0644, input->philo_num);
	resource->forks_access = sem_open(SEM_FORKS_ACCESS, O_CREAT, 0644,
		input->philo_num / 2);
	resource->full_counter = sem_open(SEM_FULL_COUNTER, O_CREAT, 0644, 0);
	resource->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (resource->forks_status == SEM_FAILED
		|| resource->forks_access == SEM_FAILED
		|| resource->full_counter == SEM_FAILED
		|| resource->sem_print == SEM_FAILED)
		return (unlink_semaphores(RET_FAILURE));
	idx = -1;
	while (++idx < input->philo_num)
		resource->sem_last_eat[idx]
			= sem_open(resource->sem_names[idx], O_CREAT, 0644, 1);
	idx = -1;
	while (++idx < input->philo_num)
		if (resource->sem_last_eat[idx] == SEM_FAILED)
			return (unlink_all(input, resource, RET_FAILURE));
	return (RET_SUCCESS);
}

int	resource_init(t_input *input, t_resource *resource)
{
	if (malloc_all(input, resource) == RET_FAILURE)
		return (RET_FAILURE);
	if (make_semaphores(input, resource) == RET_FAILURE)
		return (free_all(input, resource, RET_FAILURE));
	return (RET_SUCCESS);
}

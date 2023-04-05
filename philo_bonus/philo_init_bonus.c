#include "philo_bonus.h"

static int	input_init(t_input *input, char *argv[])
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

static int	resource_init(t_input *input, t_resource *resource)
{
	resource->status = AVAILABLE;
	resource->forks_status = sem_open(SEM_FORKS_STATUS, O_CREAT,
		0644, input->philo_num);
	resource->forks_access = sem_open(SEM_FORKS_ACCESS, O_CREAT, 0644, 1);
	resource->full_counter = sem_open(SEM_FULL_COUNTER, O_CREAT, 0644, 0);
	resource->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (resource->forks_status == SEM_FAILED
		|| resource->forks_access == SEM_FAILED
		|| resource->full_counter == SEM_FAILED
		|| resource->sem_print == SEM_FAILED)
	{
		sem_unlink(SEM_FORKS_STATUS);
		sem_unlink(SEM_FORKS_ACCESS);
		sem_unlink(SEM_FULL_COUNTER);
		sem_unlink(SEM_PRINT);
		return (RET_FAILURE);
	}
	return (RET_SUCCESS);
}

static void	info_init(t_info *info, t_input *input, t_resource *resource)
{
	info->input = input;
	info->resource = resource;
	info->eat_cnt = 0;
}

int	philo_init(t_info *info, t_input *input, t_resource *resource,
	char *argv[])
{
	if (input_init(input, argv) == RET_FAILURE)
	{
		error_msg(ERR_INPUT);
		return (RET_FAILURE);
	}
	info->pid_arr = (pid_t *) malloc(sizeof(pid_t) * input->philo_num);
	if (info->pid_arr == NULL)
		return (RET_FAILURE);
	if (resource_init(input, resource) == RET_FAILURE)
	{
		error_msg(ERR_INIT);
		free(info->pid_arr);
		return (RET_FAILURE);
	}
	info_init(info, input, resource);
	return (RET_SUCCESS);
}

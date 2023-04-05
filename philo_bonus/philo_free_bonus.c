#include "philo_bonus.h"

void	free_resource(void)
{
	sem_unlink(SEM_FORKS_ACCESS);
	sem_unlink(SEM_FORKS_STATUS);
	sem_unlink(SEM_FULL_COUNTER);
	sem_unlink(SEM_PRINT);
}

void	free_all_data(pid_t *pid_arr)
{
	free_resource();
	free(pid_arr);
}

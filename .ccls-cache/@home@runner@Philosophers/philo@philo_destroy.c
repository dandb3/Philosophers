#include "philo.h"

int	free_and_ret(void *freed1, void *freed2, void *freed3, int ret)
{
	free(freed1);
	free(freed2);
	free(freed3);
	return (ret);
}

void	mutex_destroy_until(pthread_mutex_t *forks, int cnt)
{
	int	idx;

	idx = -1;
	while (++idx < cnt)
		pthread_mutex_destroy(&forks[idx]);
	free(forks);
}

int	destroy_all(t_resource *resource, t_philo *philosophers)

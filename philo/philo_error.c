#include "philo.h"
#include "philo_msg.h"

int	error_argc(void)
{
	write(STDERR_FILENO, ERR_INPUT, ft_strlen(ERR_INPUT));
	return (EXIT_FAILURE);
}

int	error_input(void)
{
	write(STDERR_FILENO, ERR_NUM, ft_strlen(ERR_NUM));
	return (RET_FAILURE);
}

int	error_malloc(void)
{
	write(STDERR_FILENO, ERR_MALLOC, ft_strlen(ERR_MALLOC));
	return (RET_FAILURE);
}

int	error_mutex_init(void)
{
	write(STDERR_FILENO, ERR_MUTEX, ft_strlen(ERR_MUTEX));
	return (RET_FAILURE);
}

int	error_gettime(void)
{
	write(STDERR_FILENO, ERR_GETTIME, ft_strlen(ERR_GETTIME));
	return (RET_FAILURE);
}

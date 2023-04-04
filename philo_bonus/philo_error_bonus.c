#include "philo_bonus.h"

void	error_msg(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

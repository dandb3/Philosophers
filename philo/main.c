#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		error_msg(ERR_INPUT);
		return (EXIT_FAILURE);
	}
	if (philo(argv) == RET_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
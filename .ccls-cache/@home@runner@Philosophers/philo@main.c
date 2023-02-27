#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (error_argc());
	if (philo(argc, argv) == RET_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

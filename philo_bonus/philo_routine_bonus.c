#include "philo_bonus.h"

static void	philo_eat(t_info *info)
{
	usleep(100);
	hold_forks(info);
	print_msg(info, MSG_EAT);
	if (++(info->eat_cnt) == info->input->number_of_times)
		sem_post(info->resource->full_counter);
}

static void	philo_sleep(t_info *info)
{

}

static void	philo_think(t_info *info)
{
	
}

void	philo_routine(t_info *info)
{
	while (1)
	{
		philo_eat(info);
		philo_sleep(info);
		philo_think(info);
	}
}

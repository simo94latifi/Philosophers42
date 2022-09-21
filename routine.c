
#include "philo.h"

void	*routine(void *args)
{
	t_config	*instance;
	int		i;

	instance = (t_config *)args;

	i = instance->number_of_thread;
	if (instance->num_of_times_eat > 0)
	{
		while (instance->num_of_times_eat > instance->philo[i].num_of_times_ate && instance->philo_dead == FALSE){
			
			printf("!");
			//routine_execute(instance, i);
		}
	}
	else
	{
		while (instance->philo_dead == FALSE)
		{
			//if (routine_execute(instance, i) == FALSE)
				break ;
		}
	}
	return (NULL);
}


#include "philo.h"

int	philo_eat(t_config *instance, int i)
{
    
	if (pthread_mutex_lock(&instance->forks[instance->philo[i].fork->left]) != 0)
		return (FALSE);
	if (philo_print(instance, instance->philo[i].id, FORK) == FALSE)
		return (FALSE);
	if (pthread_mutex_lock(&instance->forks[instance->philo[i].fork->right]) != 0)
		return (FALSE);
	if (philo_print(instance, instance->philo[i].id, FORK) == FALSE)
		return (FALSE);
	if (philo_print(instance, instance->philo[i].id, EAT) == FALSE)
		return (FALSE);
	instance->philo[i].time_to_die = get_time();
	
    usleep(instance->philo[i].time_to_eat * 1000);
	drop_forks(instance, i);
    
	return (TRUE);
}

int drop_forks(t_config *instance, int i)
{

    
    if(pthread_mutex_unlock(&instance->forks[instance->philo[i].fork->left]) != 0 )
        return (FALSE);
    if(pthread_mutex_unlock(&instance->forks[instance->philo[i].fork->right]) != 0 )
        return (FALSE);
    instance->philo[i].num_of_times_ate++;
    return (TRUE);

}
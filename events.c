#include "philo.h"

int	philo_eat(t_config *instance, int i)
{
    
	if (pthread_mutex_lock(&instance->forks[instance->philo[i].fork_left]) != 0)
		return (FALSE);
	if (philo_print(instance, instance->philo[i].id, FORK_LEFT) == FALSE)
		return (FALSE);
	if (pthread_mutex_lock(&instance->forks[instance->philo[i].fork_right]) != 0)
		return (FALSE);
	if (philo_print(instance, instance->philo[i].id, FORK_RIGHT) == FALSE)
		return (FALSE);
	if (philo_print(instance, instance->philo[i].id, EAT) == FALSE)
		return (FALSE);
	
	instance->philo[i].last_meal = get_time(); //105
	//printf("last meal of philo id : %d is : %lld  time config is : %lld \n \n",instance->philo[i].id, instance->philo[i].last_meal, instance->input_time_to_die  );
	//instance->philo[i].time_to_die = get_time();
    //usleep(instance->philo[i].time_to_eat * 1000);
	ft_sleep(instance->philo[i].time_to_eat);
	drop_forks(instance, i);
	    
	return (TRUE);
}

int	philo_sleep(t_config *instance, int i)
{
	if (philo_print(instance, i, SLEEP) == FALSE)
		return (FALSE);
	//usleep(instance->philo[i].time_to_sleep * 1000);
	ft_sleep(instance->philo[i].time_to_sleep);
	return (TRUE);
}

int	philo_think(t_config *instance, int i)
{
	if (philo_print(instance, instance->philo[i].id, THINK) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	philo_is_dead(t_config *instance, int *i)
{
	long long	time;

	if (*i == instance->num_philo)
		*i = 0;
	time = delta_time(instance->philo[*i].last_meal);
	if (time >= instance->input_time_to_die)
	{
		philo_print(instance, instance->philo[*i].id, DIED);
		instance->philo_dead = TRUE;
		return (TRUE);
	}
	i++;
	return (FALSE);
}

int drop_forks(t_config *instance, int i)
{

    if(pthread_mutex_unlock(&instance->forks[instance->philo[i].fork_left]) != 0 )
        return (FALSE);
    if(pthread_mutex_unlock(&instance->forks[instance->philo[i].fork_right]) != 0 )
        return (FALSE);
    instance->philo[i].num_of_times_ate++;
    return (TRUE);

}


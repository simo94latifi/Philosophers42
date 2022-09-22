#include "philo.h"


int create_philos(t_config *instance, int argc, char **argv)
{
    int i;
    int j;
    instance->num_philo = ft_atoi(argv[1]);
    instance->philo = malloc(sizeof(t_philosopher) * (instance->num_philo + 1));
    if (instance->philo == NULL)
        return (FALSE);
    i = 0;
    j= 1;
    while( j <  instance->num_philo)
    {
        fill_philo_struct(instance, i, j, argc, argv);
		j++;
        i++;
    }
    j = 0;
	fill_philo_struct(instance, i, j, argc, argv);
	return (TRUE);
}

int	create_threads(t_config *instance)
{
	int i;

	i = 0;
	instance->philo_dead = FALSE;
	instance->timing = get_time();
	if(pthread_mutex_init(&instance->write, NULL) != 0)
		return (FALSE);
	
	while (i < instance->num_philo)
	{
		instance->number_of_thread = i;
		if(pthread_create(&instance->philo[i].thread, NULL, &routine, (void *) instance) != 0)
			return (FALSE);
		i++;
		usleep(1000);
	}
	if (join_threads(instance) == FALSE)
		return (FALSE);
	return (TRUE);
	
}
int	join_threads(t_config *instance)
{
	int	i;

	i = 0;
	while (i < instance->num_philo)
	{
		if (pthread_join(instance->philo[i].thread, NULL) != 0)
			return (FALSE);
		i++;
	}
	
	if (pthread_join(instance->ping, NULL) != 0)
		return (FALSE);
	
	return (TRUE);
}

int create_forks(t_config *instance)
{
	int i;
	
	i = 0;
	instance->forks = malloc(sizeof(pthread_mutex_t) * instance->num_philo + 1);
	if(instance->forks == NULL)
		return (FALSE);
	while(i < instance->num_philo)
	{
		if(pthread_mutex_init(&instance->forks[i], NULL) != 0)
			return (FALSE);
	}
	return (TRUE);
}


int fill_philo_struct(t_config *instance, int lf, int rf, int argc, char **argv){

    instance->philo[lf].id = lf + 1;
	instance->philo[lf].num_of_times_ate = 0;
	//instance->forks[instance->philo[lf].fork->left] = lf;
	instance->philo[lf].fork->left = lf;
	instance->philo[lf].fork->right = rf;

    if (argc == 5 || argc == 6)
	{
		instance->philo[lf].time_to_die = ft_atoi(argv[2]);
		instance->philo[lf].time_to_eat = ft_atoi(argv[3]);
		instance->philo[lf].time_to_sleep = ft_atoi(argv[4]);
		instance->num_of_times_eat = -1;
        if(argc == 6)
            instance->num_of_times_eat = ft_atoi(argv[5]);
        
		return (TRUE);
	}
	return (FALSE);    

}

int	ft_atoi(const char *str)
{
	size_t	c;
	int		s;
	int		res;

	c = 0;
	s = 1;
	res = 0;
	while ((str[c] >= 9 && str[c] <= 13) || str[c] == 32)
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s *= -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (str[c] - '0') + (res * 10);
		c++;
	}
	return (res * s);
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

int	philo_print(t_config *instance, int id, char *status)
{
	long long	now;

	now = delta_time(instance->timing);
	if (instance->philo_dead == TRUE)
		return (FALSE);
	pthread_mutex_lock(&instance->write);
	if (instance->philo_dead == TRUE)
	{
		pthread_mutex_unlock(&instance->write);
		return (FALSE);
	}
	else
		printf("%-10lld %-3d %-30s \n", now, id, status);
	pthread_mutex_unlock(&instance->write);
	return (TRUE);
}
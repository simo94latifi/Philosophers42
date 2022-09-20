#include "philo.h"

/*

int init_config(int argc, char **argv, t_config *config)
{

}

int	create_threads(t_config *config)
{
	int	i;

	i = 0;
	config->philo_dead = FALSE;
	config->timing = get_time();
	if (pthread_mutex_init(&config->write, NULL) != 0)
		return (FALSE);
	while (i < config->num_philo)
	{
		//config->id = i;
		if (pthread_create(&config->philo[i].thread,
				NULL, &routine, (void *) config) != 0)
			return (FALSE);
		i++;
		usleep(1000);
	}
	if (pthread_create(&config->ping, NULL, &checker, (void *) config) != 0)
		return (FALSE);
	usleep(1000);
	if (join_threads(config) == FALSE)
		return (FALSE);
	return (TRUE);
}


int	join_threads(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_philo)
	{
		if (pthread_join(config->philo[i].thread, NULL) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_join(config->ping, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

void	*checker(void *args)
{
	t_config	*config;
	int		i;

	config = (t_config *)args;
	i = 0;
	if (config->num_of_times_eat > 0)
	{
		while (config->num_of_times_eat > config->philo[i].num_of_times_ate
			&& config->philo_dead == FALSE)
		{
			if (philo_is_dead(config, &i) == TRUE)
				break ;
		}
	}
	else
	{
		while (config->philo_dead == FALSE)
		{
			if (philo_is_dead(config, &i) == TRUE)
				break ;
		}
	}
	return (NULL);
}

int	philo_is_dead(t_config *config, int *i)
{
	int	time;

	if (*i == config->num_philo)
		*i = 0;
	time = delta_time(config->philo[*i].time_to_die);
	if (time > main->input.time_to_die)
	{
		philo_print(main, main->philo[*i].id, PINK, DIED);
		main->philo_dead = TRUE;
		return (TRUE);
	}
	i++;
	return (FALSE);
}
*/
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


int fill_philo_struct(t_config *instance, int lf, int rf, int argc, char **argv){

	
    instance->philo[lf].id = lf + 1;
	instance->philo[lf].num_of_times_ate = 0;
	instance->philo[lf].left_fork = lf;
	instance->philo[lf].right_fork = rf;

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

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

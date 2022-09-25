#include "philo.h"


int create_philos(t_config *instance, int argc, char **argv)
{
    int i;
    int j;
    instance->num_philo = ft_atoi(argv[1]);
    instance->philo = malloc(sizeof(t_philosopher) * instance->num_philo);

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
	instance->timing = get_time(); //100
	if(pthread_mutex_init(&instance->write, NULL) != 0)
		return (FALSE);
	
	usleep(10);
	//ft_sleep(10);
	while (i < instance->num_philo)
	{
		if(pthread_create(&instance->philo[i].thread, NULL, &routine, (void *) instance) != 0)
			return (FALSE);
		instance->number_of_thread = i;
		i++;
		usleep(10);
		//ft_sleep(10);
	}
	if(pthread_create(&instance->ping, NULL, &check, (void *) instance) != 0)
		return (FALSE);
	usleep(10);

	
	//ft_sleep(20);
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
		usleep(10);
	}
	
	if (pthread_join(instance->ping, NULL) != 0)
		return (FALSE);
	
	return (TRUE);
}

int	destroy_threads(t_config *instance)
{
	int	i;

	i = 0;
	while (i < instance->num_philo)
	{
		pthread_mutex_destroy(&instance->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&instance->write);
	return (TRUE);
}


int create_forks(t_config *instance)
{
	int i;
	
	i = 0;
	instance->forks = malloc(sizeof(pthread_mutex_t) * instance->num_philo);
	if(instance->forks == NULL)
		return (FALSE);
	

	while(i < instance->num_philo)
	{
		if(pthread_mutex_init(&instance->forks[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}


int fill_philo_struct(t_config *instance, int lf, int rf, int argc, char **argv){

    instance->philo[lf].id = lf;
	instance->philo[lf].num_of_times_ate = 0;
	//instance->forks[instance->philo[lf].fork->left] = lf;


	//(void)rf;

	//instance->philo[lf]->fork->left = lf;
	//instance->philo[lf].fork->right = rf;
	//instance->philo[lf].fork[lf].left = 1;
	/*
	argv1 number_of_philosophers 
	argv2 time_to_die 
	argv3 time_to_eat 
	argv4 time_to_sleep 
	optional argv5 [number_of_times_each_philosopher_must_eat]
	*/
	instance->philo[lf].fork_left = lf;
	instance->philo[lf].fork_right = rf;

    if (argc == 5 || argc == 6)
	{
		instance->input_time_to_die = ft_atoi(argv[2]);
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
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / (uint64_t)1000));
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
		printf("%lld %d %s\n", now, id + 1, status);
	pthread_mutex_unlock(&instance->write);
	return (TRUE);
}


void	ft_sleep(long long time)
{
	long long	tmp;

	tmp = get_time();
	usleep(time * 1000 - 20000);
	while (get_time() < tmp + time)
		continue ;
}


void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void ft_free(t_config *instance)
{

    free(instance->forks);
    free(instance->philo);

}

int	ft_isdigit(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0'){
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

int	check_inputs(int argc, char **argv)
{
	if(argc == 5 || argc == 6){

		if(ft_isdigit(argv[1]) && ft_atoi(argv[1]) > 0)
			return (TRUE);

		if(ft_isdigit(argv[2]) && ft_atoi(argv[2]) > 0)
			return (TRUE);

		if(ft_isdigit(argv[3]) && ft_atoi(argv[3]) > 0)
			return (TRUE);

		if(ft_isdigit(argv[4]) && ft_atoi(argv[4]) > 0)
			return (TRUE);
		if(argc == 6){
			if(ft_isdigit(argv[5]) && ft_atoi(argv[5]) > 0)
			return (TRUE);
		}

	}
	return (FALSE);
}
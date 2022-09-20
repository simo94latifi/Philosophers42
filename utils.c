#include "philo.h"



int init_config(int argc, char **argv, t_config *config)
{
	if (argc == 5 || argc == 6)
	{
		config->num_philo = ft_atoi(argv[1]);
		config->time_to_die = ft_atoi(argv[2]);
		config->time_to_eat = ft_atoi(argv[3]);
		config->time_to_sleep = ft_atoi(argv[4]);
		config->num_of_times_eat = -1;
        if(argc == 6)
            config->num_of_times_eat = ft_atoi(argv[5]);
        
		return (TRUE);
	}
	return (FALSE);
}
int create_philos(t_config *instance)
{
    int i;
    int j;

    instance->philo = malloc(sizeof(t_philosopher) * (instance->num_philo + 1));
    if (instance->philo == NULL)
        return (FALSE);
    i = 0;
    j= 1;
    while( j <  instance->num_philo)
    {
        fill_philo_struct(instance, i, j);
		j++;
        i++;
    }
    j = 0;
	fill_philo_struct(instance, i, j);
	return (TRUE);
}


void    fill_philo_struct(t_config *instance, int lf, int rf){

    instance->philo[lf].id = lf + 1;
	instance->philo[lf].num_of_times_ate = 0;
	//instance->philo[lf].time_to_die = 0;
	instance->philo[lf].left_fork = lf;
	instance->philo[lf].right_fork = rf;
    

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
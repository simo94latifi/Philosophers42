#ifndef PHILO_H
# define PHILO_H

#include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>


# define TRUE 1
# define FALSE 0


# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK_LEFT "has taken a left fork"
# define FORK_RIGHT "has taken a right fork"
# define DIED "died"


typedef struct s_fork
{
	int				left;
	int				right;
}					t_fork;


typedef struct s_philosopher
{
    pthread_t		thread;

	int				id;
    int             fork_left;
    int             fork_right;
    int             num_of_times_ate;
    //long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;

    long long       last_meal;

}					t_philosopher;



typedef struct s_config
{
    int             number_of_thread;
    int             num_philo;
    int             num_of_times_eat;
    long long       input_time_to_die;
    int             philo_dead;
    long long       timing;

    pthread_mutex_t	        write;
    pthread_t               ping;
    t_philosopher           *philo;
    pthread_mutex_t         *forks;

}                   t_config;

int         create_philos(t_config *instance, int argc, char **argv);
int         fill_philo_struct(t_config *instance, int lf, int rf, int argc, char **argv);
int	        ft_atoi(const char *str);
int         init_config(int argc, char **argv, t_config *config);
int	        create_threads(t_config *instance);
int         create_forks(t_config *instance);
long long	get_time(void);
void	    *routine(void *args);
int	        join_threads(t_config *instance);
int         philo_eat(t_config *instance, int i);
int	        philo_print(t_config *instance, int id, char *status);
long long	delta_time(long long time);

int	philo_eat(t_config *instance, int i);
int philo_sleep(t_config *instance, int i);
int	philo_is_dead(t_config *instance, int *i);
int	philo_think(t_config *instance, int i);

void	*checker(void *args);

int routine_execute(t_config *instance, int i);
int drop_forks(t_config *instance, int i);
void	*check(void *args);
void	ft_sleep(long long time);
int	destroy_threads(t_config *instance);
#endif

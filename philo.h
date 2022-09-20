#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>


/*
** bool
*/
# define TRUE 1
# define FALSE 0



/*
** Error messages
*/
# define NUM_ARGS "ERROR: The number of argments must be 4 or 5"
# define ARG1 "ERROR: There is a mistake in number of philosophers"
# define ARG2 "ERROR: There is a mistake in time to die"
# define ARG3 "ERROR: There is a mistake in time to eat"
# define ARG4 "ERROR: There is a mistake in time to sleep"
# define ARG5 "ERROR: There is a mistake in number of times each philosopher must eat"
# define HELP "The number of argments must be 4 or 5:\n\
- arg1 number of philosophers\n\
- arg2 time to die\n\
- arg3 time to eat\n\
- arg4 time to sleep\n\
- arg5 number of times each philosopher must eat (optional)"

/*
** Routines messages
*/
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"

/*
** Structures
*/

typedef struct s_philosopher
{
    pthread_t		thread;
	int				id;
    int             left_fork;
    int             right_fork;
    int             num_of_times_ate;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;

    pthread_mutex_t	*forks;

}					t_philosopher;

typedef struct s_config
{
    int             number_of_thread;
    int             num_philo;
    int             num_of_times_eat;

    int             philo_dead;
    long long       timing;
    pthread_mutex_t	write;
    pthread_t       ping;
    t_philosopher   *philo;

}                   t_config;

int         create_philos(t_config *instance, int argc, char **argv);
int         fill_philo_struct(t_config *instance, int lf, int rf, int argc, char **argv);
int	        ft_atoi(const char *str);
int         init_config(int argc, char **argv, t_config *config);
int	        create_threads(t_config *config);
long long	get_time(void);
/*
void	    *routine(void *args)
*/
#endif

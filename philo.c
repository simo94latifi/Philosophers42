#include "philo.h"

int main(int argc, char **argv)
{

    t_config demo;


    create_philos(&demo, argc, argv);
    create_forks(&demo);
    create_threads(&demo);


    return (0);

}
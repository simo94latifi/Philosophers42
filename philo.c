#include "philo.h"

int main(int argc, char **argv)
{

    t_config demo;

    init_config(argc, argv, &demo);
    printf(" number of philo : %d ", demo.num_philo );
    create_philos(&demo);

    int i = 0;
    while(i < 5){

        printf("\n id : %d ", demo.philo[i].id);
        printf("\n leftf : %d ", demo.philo[i].left_fork);
        printf("\n rightf : %d \n", demo.philo[i].right_fork);
        
        i++;
    }

    return (0);

}
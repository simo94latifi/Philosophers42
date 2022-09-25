#include "philo.h"


void ft_free(t_config *instance)
{

    free(instance->forks);
    free(instance->philo);

}
int main(int argc, char **argv)
{

    t_config demo;
    

    if (create_philos(&demo, argc, argv) == FALSE)
      return (1);
    if (create_forks(&demo) == FALSE)
      return (1);

    if (create_threads(&demo) == FALSE)
      return (1);
    if (destroy_threads(&demo) == FALSE)
      return (1);
    ft_free(&demo);
    /*
    */

    /*
   int i = 0;

   while(i < demo.num_philo){
    printf("Philo ID : %d \n", demo.philo[i].id);
    printf("Fork left : %d \n", demo.philo[i].fork_left);
    printf("Fork Right : %d \n", demo.philo[i].fork_right);
    i++;
   }
    */



    return (0);

}
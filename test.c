#include "philo.h"

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

int main (int argc, char **argv){

   

   printf("count : %d val : %d \n", argc, ft_isdigit(argv[1]));
}
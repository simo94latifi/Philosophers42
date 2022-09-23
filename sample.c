int	routine_execute(t_main *main, int i)
{
	if (philo_eat(main, i) == FALSE)
		return (FALSE);
	if (main->input.num_of_times_eat != main->philo[i].num_of_times_ate)
	{
		if (philo_sleep(main, i) == FALSE)
			return (FALSE);
		if (philo_think(main, i) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
int	philo_sleep(t_main *main, int i)
{
	if (philo_print(main, main->philo[i].id, BLUE, SLEEP) == FALSE)
		return (FALSE);
	exec_action(main->input.time_to_sleep);
	return (TRUE);
}

int	philo_think(t_main *main, int i)
{
	if (philo_print(main, main->philo[i].id, G_BLUE, THINK) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	philo_is_dead(t_main *main, int *i)
{
	int	time;

	if (*i == main->input.num_philo)
		*i = 0;
	time = delta_time(main->philo[*i].time_to_die);
	if (time > main->input.time_to_die)
	{
		philo_print(main, main->philo[*i].id, PINK, DIED);
		main->philo_dead = TRUE;
		return (TRUE);
	}
	i++;
	return (FALSE);
}
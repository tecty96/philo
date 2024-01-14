/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:25:09 by apetre            #+#    #+#             */
/*   Updated: 2024/01/03 19:25:09 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->eat_or_die = ft_atoi(av[2]);
	data->meal_duration = ft_atoi(av[3]);
	data->sleeping_time = ft_atoi(av[4]);
	if (av[5])
		data->max_meals = ft_atoi(av[5]);
	else
		data->max_meals = -1;
	data->philos = (t_philo *) malloc(data->nb_philos * sizeof(t_philo));
	data->philos_ids = (pid_t *) malloc(data->nb_philos * sizeof(pid_t));
	memset(data->philos, 0, data->nb_philos * sizeof(t_philo));
	sem_unlink("forks_to_eat");
	sem_unlink("stop");
	sem_unlink("print");
	sem_unlink("ck_eat_or_die");
	sem_unlink("take_forks");
	sem_unlink("meal_counter");
	sem_unlink("check_time");
	data->forks_to_eat = sem_open("forks_to_eat", O_CREAT | O_EXCL, S_IXUSR,  data->nb_philos);
	data->stop = sem_open("stop", O_CREAT | O_EXCL, S_IXUSR,  0);
	data->print = sem_open("print", O_CREAT | O_EXCL, S_IXUSR,  1);
	data->check_eat_or_die = sem_open("ck_eat_or_die", O_CREAT | O_EXCL, S_IXUSR,  1);
	data->take_forks = sem_open("take_forks", O_CREAT | O_EXCL, S_IXUSR,  1);
	data->meal_counter = sem_open("meal_counter", O_CREAT | O_EXCL, S_IXUSR,  1);

}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	gettimeofday(&data->genesis, NULL);
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meal_counter = data->max_meals;
		data->philos[i].eat_or_die = data->eat_or_die;
		data->philos_ids[i] = fork();
		if (data->philos_ids[i] == 0)
			child_routine(&data->philos[i]);
		i++;
	}
}

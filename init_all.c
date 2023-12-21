/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:44:13 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 23:11:55 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	init_data(t_data *data, char **av)
{
	int	i;
	
	i = 0;
	data->nb_philos = ft_atoi(av[1]);
	data->eat_or_die = ft_atoi(av[2]);
	data->meal_duration = ft_atoi(av[3]);
	data->sleeping_time = ft_atoi(av[4]);
	if (av[5])
		data->max_meals = ft_atoi(av[5]);
	else
		data->max_meals = -1;
	data->philos = (t_philo *) malloc(data->nb_philos * sizeof(t_philo));
	memset(data->philos, 0, data->nb_philos * sizeof(t_philo));
	data->forks = (pthread_mutex_t *) malloc(data->nb_philos * sizeof(pthread_mutex_t));
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].main_check, NULL);
		i++;
	}
	pthread_mutex_init(&data->check_dead, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->check_rightnow, NULL);
			
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
		if (i == 0)
		{
			data->philos[i].lfork =  &data->forks[data->nb_philos - 1];
			data->philos[i].rfork =  &data->forks[i];
		}
		else
		{
			data->philos[i].lfork =  &data->forks[i - 1];
			data->philos[i].rfork =  &data->forks[i];
		}
		data->philos[i].eat_or_die = data->eat_or_die;
		pthread_create(&data->philos[i].core, NULL, &philo_routine, &data->philos[i]);
		i++;
	}
}

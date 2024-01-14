/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:19:44 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 23:32:01 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_all_to_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].main_check);
		data->philos[i].dead = 1;
		pthread_mutex_unlock(&data->philos[i].main_check);
		i++;
	}
}

int	check_death_timer(t_data *data, int i, int *time)
{
	pthread_mutex_lock(&data->philos[i].main_check);
	if (*time > data->philos[i].eat_or_die)
	{
		pthread_mutex_unlock(&data->philos[i].main_check);
		data->dead = 1;
		set_all_to_dead(data);
		pthread_mutex_lock(&data->print);
		printf("%d %d has died!\n", *time, data->philos[i].id);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].main_check);
	return (0);
}

void	init_all(t_data *data, char **av)
{
	memset((void *) data, 0, sizeof(*data));
	init_data(data, av);
	init_philos(data);
}

int	check_all_philos_meal_counter(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].main_check);
		if (data->philos[i].meal_counter == 0)
		{
			pthread_mutex_unlock(&data->philos[i].main_check);
			i++;
		}
		else
		{
			pthread_mutex_unlock(&data->philos[i].main_check);
			return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	int		time;

	if (error(ac, av))
		return (1);
	init_all(&data, av);
	while (data.philos[0].dead != 1)
	{
		if (check_all_philos_meal_counter(&data))
			break ;
		i = 0;
		while (i < data.nb_philos)
		{
			gettimeofday(&data.data_rightnow, NULL);
			time = data_time_rn(&data);
			if (check_death_timer(&data, i, &time))
				break ;
			i++;
		}
	}
	pthread_mutex_unlock(&data.print);
	fin(&data);
	return (0);
}

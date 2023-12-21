/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:47:33 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 07:48:25 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fin(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->nb_philos)
		pthread_join(data->philos[i++].core, NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}	
	free(data->philos);	
	free(data->forks);
	pthread_mutex_destroy(&data->check_dead);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->check_rightnow);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:14:30 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 22:58:31 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_rn(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->check_rightnow);
	gettimeofday(&philo->rightnow, NULL);
	time = (philo->rightnow.tv_sec * 1000 + philo->rightnow.tv_usec / 1000)
		- (philo->data->genesis.tv_sec * 1000
			+ philo->data->genesis.tv_usec / 1000);
	return (pthread_mutex_unlock(&philo->data->check_rightnow), time);
}

int	data_time_rn(t_data *data)
{
	int	time;

	gettimeofday(&data->data_rightnow, NULL);
	time = (data->data_rightnow.tv_sec * 1000)
		+ (data->data_rightnow.tv_usec / 1000)
		- (data->genesis.tv_sec * 1000 + data->genesis.tv_usec / 1000);
	return (time);
}

int	check_this_philo_state(t_philo *philo)
{
	int	time_rightnow;

	time_rightnow = time_rn(philo);
	if (time_rightnow > philo->eat_or_die)
	{
		check_print("has died!\n", time_rightnow, philo);
		pthread_mutex_lock(&philo->data->check_dead);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->check_dead);
		return (1);
	}
	if (philo->data->max_meals > 0 && philo->meal_counter == 0)
		return (1);
	return (0);
}

int	check_if_any_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_dead);
	if (philo->data->dead == 1)
		return (pthread_mutex_unlock(&philo->data->check_dead), 1);
	pthread_mutex_unlock(&philo->data->check_dead);
	return (0);
}

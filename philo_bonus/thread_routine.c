/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 08:42:39 by apetre            #+#    #+#             */
/*   Updated: 2024/01/03 08:42:39 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	while (1)
	{
		sem_wait(philo->data->check_eat_or_die);
		sem_wait(philo->data->meal_counter);
		if (time_rn_thread(philo) >= philo->eat_or_die && philo->meal_counter != 0)
		{
			sem_wait(philo->data->print);
			printf("%d %d has died!\n", time_rn_philo(philo), philo->id);
			sem_post(philo->data->stop);
			sem_post(philo->data->meal_counter);
			sem_post(philo->data->check_eat_or_die);
			break ;
		}
		sem_post(philo->data->meal_counter);
		sem_post(philo->data->check_eat_or_die);
		sem_wait(philo->data->meal_counter);
		if (philo->data->finished_meals == philo->data->nb_philos * philo->data->max_meals)
		{
			sem_post(philo->data->stop);
			sem_post(philo->data->meal_counter);
			break ;
		}
		sem_post(philo->data->meal_counter);
	}
	return (NULL);
}
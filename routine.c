/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:04:55 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 22:46:24 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_check);
	if(philo->dead == 1)
	{		
		pthread_mutex_unlock(&philo->main_check);	
		return (1);
	}
	pthread_mutex_unlock(&philo->main_check);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	if (philo->id % 2)
		slumber(philo, philo->data->meal_duration);
	 while (1)
	 {
		if (philo->meal_counter == 0)
			break ;
		if (check_death(philo))
			break ;
		thinking(philo);
		eating(philo);
		sleeping(philo);
		if (check_death(philo))
			break ;
	}
	return (NULL);
}
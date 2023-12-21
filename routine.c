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

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	 while (1)
	 {
		//if (check_if_any_died(philo))
			// return (NULL);
		//if (check_this_philo_state(philo))
			// return (NULL);
		//if (!check_if_any_died(philo))
		pthread_mutex_lock(&philo->data->print);
		printf("\t\t%d philo dead = %p\n", time_rn(philo), &philo->dead);	
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_lock(&philo->main_check);
		if(philo->dead == 1)
		{		
			pthread_mutex_unlock(&philo->main_check);	
			break ;
		}
		pthread_mutex_unlock(&philo->main_check);
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d is thinking\n", time_rn(philo), philo->id);	
		pthread_mutex_unlock(&philo->data->print);
			//check_print("is thinking!\n", time_rn(philo), philo);
		//if (check_if_any_died(philo))
			// return (NULL);
		//if (check_this_philo_state(philo))
			// return (NULL);
		//if (check_if_any_died(philo))
			eating(philo);
		//if (check_if_any_died(philo))
			sleeping(philo);
		pthread_mutex_lock(&philo->main_check);
		if(philo->dead == 1)
		{		
			pthread_mutex_unlock(&philo->main_check);	
			break ;
		}
		pthread_mutex_unlock(&philo->main_check);

	}
	return (NULL);
}

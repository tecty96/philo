/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:49:59 by apetre            #+#    #+#             */
/*   Updated: 2024/01/03 19:49:59 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	child_routine(t_philo *philo)
{
	pthread_create(&philo->reaper, NULL, &reaper_routine, philo);
	pthread_detach(philo->reaper);
	while (1)
	 {
		thinking(philo);
		eating(philo);
		if (philo->meal_counter == 0)
			exit(0);
		sleeping(philo);
	}
}
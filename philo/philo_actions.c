/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:08:51 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 23:15:32 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%d %d is thinking!\n", time_rn(philo), philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	sleeping(t_philo *philo)
{
	check_print("is sleeping!\n", time_rn(philo), philo);
	slumber(philo, philo->data->sleeping_time);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->data->take_forks);
		pthread_mutex_lock(philo->rfork);
		check_print("has taken the right fork!\n", time_rn(philo), philo);
		pthread_mutex_lock(philo->lfork);
		check_print("has taken the left fork!\n", time_rn(philo), philo);
		pthread_mutex_unlock(&philo->data->take_forks);
	}
	else
	{
		pthread_mutex_lock(&philo->data->take_forks);
		pthread_mutex_lock(philo->lfork);
		check_print("has taken the left fork!\n", time_rn(philo), philo);
		pthread_mutex_lock(philo->rfork);
		check_print("has taken the right fork!\n", time_rn(philo), philo);
		pthread_mutex_unlock(&philo->data->take_forks);
	}
}

void	eating(t_philo *philo)
{
	take_fork(philo);
	philo->temp_time = time_rn(philo);
	check_print("is eating!\n", philo->temp_time, philo);
	pthread_mutex_lock(&philo->main_check);
	philo->eat_or_die = philo->temp_time + philo->data->eat_or_die;
	pthread_mutex_unlock(&philo->main_check);
	if (philo->meal_counter > 0)
		philo->meal_counter--;
	slumber(philo, philo->data->meal_duration);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:59:34 by apetre            #+#    #+#             */
/*   Updated: 2024/01/03 19:59:34 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	sem_wait(philo->data->print);
	printf("%d %d is thinking!\n", time_rn_philo(philo), philo->id);	
	sem_post(philo->data->print);
}

void	sleeping(t_philo *philo)
{
	sem_wait(philo->data->print);
	printf("%d %d is sleeping!\n", time_rn_philo(philo), philo->id);	
	sem_post(philo->data->print);
	usleep(philo->data->sleeping_time * 1000);
}

void	take_fork(t_philo *philo)
{
	int	i;

	i = 0;
	sem_wait(philo->data->take_forks);
	while (i < 2)
	{
		sem_wait(philo->data->forks_to_eat);
		sem_wait(philo->data->print);
		printf("%d %d has taken a fork!\n", time_rn_philo(philo), philo->id);
		sem_post(philo->data->print);
		i++;
	}
	sem_post(philo->data->take_forks);
}

void	eating(t_philo *philo)
{
	take_fork(philo);
	
	philo->temp_time = time_rn_philo(philo);
	
	sem_wait(philo->data->print);
	printf("%d %d is eating!\n", philo->temp_time, philo->id);
					printf("TIME RN %d\n", philo->temp_time);

	sem_post(philo->data->print);

	sem_wait(philo->data->check_eat_or_die);
	philo->eat_or_die = philo->temp_time + philo->data->eat_or_die;
		sem_wait(philo->data->print);

				printf("TIME TO DIE %d\n", philo->eat_or_die);
		sem_post(philo->data->print);

	sem_post(philo->data->check_eat_or_die);
	sem_wait(philo->data->meal_counter);
	if (philo->meal_counter > 0)
	{
		philo->meal_counter--;
		philo->data->finished_meals++;
	}
	if (philo->meal_counter == 0)
	{
		sem_post(philo->data->meal_counter);
		exit (0);
	}
	sem_post(philo->data->meal_counter);
	usleep(philo->data->meal_duration * 1000);
	sem_post(philo->data->forks_to_eat);
	sem_post(philo->data->forks_to_eat);
}

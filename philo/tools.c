/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:45:29 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 23:18:24 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	minus;
	int	result;

	minus = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			minus = minus * (-1);
		nptr++;
	}
	while ((*nptr >= 48 && *nptr <= 57))
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	return (result * minus);
}

size_t	ft_strlen_no_spaces(char *str)
{
	size_t	i;

	i = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

size_t	count_size_in_chars(int n)
{
	size_t	size_in_chars;

	size_in_chars = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size_in_chars++;
	while (n != 0)
	{
		n = n / 10;
		size_in_chars++;
	}
	return (size_in_chars);
}

void	check_print(char *str, int time, t_philo *philo)
{
	pthread_mutex_lock(&philo->main_check);
	if (philo->dead != 0 || philo->meal_counter == 0 || philo->data->dead)
	{
		pthread_mutex_unlock(&philo->main_check);
		return ;
	}
	pthread_mutex_unlock(&philo->main_check);
	pthread_mutex_lock(&philo->data->print);
	printf("%d %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	slumber(t_philo *philo, int endofwinter)
{
	int	target_time;
	int	now;

	now = time_rn(philo);
	target_time = now + endofwinter;
	if (check_if_any_died(philo))
		return ;
	while (now <= target_time)
	{
		now = time_rn(philo);
		pthread_mutex_lock(&philo->main_check);
		if (philo->dead == 1)
		{
			pthread_mutex_unlock(&philo->main_check);
			break ;
		}
		pthread_mutex_unlock(&philo->main_check);
	}
}

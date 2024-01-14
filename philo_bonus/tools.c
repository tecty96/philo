/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:07:27 by apetre            #+#    #+#             */
/*   Updated: 2024/01/03 20:07:27 by apetre           ###   ########.fr       */
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
	size_t i;

	i = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while(*str)
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

int	time_rn_philo(t_philo *philo)
{
	int	time;

	gettimeofday(&philo->philo_time, NULL);
	time = (philo->philo_time.tv_sec * 1000 + philo->philo_time.tv_usec / 1000)
			- (philo->data->genesis.tv_sec * 1000 + philo->data->genesis.tv_usec / 1000);
	return (time);	
}

int	time_rn_thread(t_philo *philo)
{
	int	time;

	gettimeofday(&philo->thread_time, NULL);
	time = (philo->thread_time.tv_sec * 1000) + (philo->thread_time.tv_usec / 1000)
			- (philo->data->genesis.tv_sec * 1000 + philo->data->genesis.tv_usec / 1000);
	return (time);	
}


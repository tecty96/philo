/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:23:48 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 11:16:15 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

static int	is_there_any_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	if_one(int *time, char **av)
{
	printf("%d 1 has taken the left fork!\n", 0);
	usleep(*time * 1000);
	printf("%d 1 has died!\n", ft_atoi(av[2]));
}

int	check_rest(char **av)
{
	int	i;
	int	check;

	i = 2;
	check = 0;
	while (av[i])
	{
		if (check_string(av[i]))
			return (printf("Expecting only numbers and whitespaces!\n"), 1);
		check = ft_atoi(av[i]);
		if (ft_strlen_no_spaces(av[i]) != count_size_in_chars(check))
			return (printf("Argument is overflowing!\n"), 1);
		if (check < 1)
			return (printf("The given values should be positive!\n"), 1);
		i++;
	}
	return (0);
}

int	error(int ac, char **av)
{
	int		time;

	if (ac >= 3)
		time = ft_atoi(av[2]);
	if (ac < 5 || ac > 6 || ac == 2)
	{
		if (ac == 2 && is_there_any_space(av[1]))
			return (printf("Please separate the arguments one by one!\n"), 1);
		else
			return (printf("Wrong number of arguments!\n"), 1);
	}
	if (av[1][0] == '0')
		return (printf("At least one philisopher expected!\n"), 1);
	if (ft_atoi(av[1]) == 1)
		return (if_one(&time, av), 1);
	if (check_rest(av))
		return (1);
	return (0);
}

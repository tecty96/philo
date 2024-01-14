/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:54:57 by apetre            #+#    #+#             */
/*   Updated: 2024/01/03 09:54:57 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_all(t_data *data, char **av)
{
	memset((void *) data, 0, sizeof(*data));
	init_data(data, av);
	init_philos(data);
}

int	main(int ac, char **av)
{
	t_data data;
	int	i;
	
	i = 0;
	if (error(ac, av))
	 	return (1);
	init_all(&data, av);
	sem_wait(data.stop);
	while (i < data.nb_philos)
	{
		kill(data.philos_ids[i], SIGKILL);
		i++;
	}
	sem_post(data.print);
}
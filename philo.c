/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:19:44 by apetre            #+#    #+#             */
/*   Updated: 2023/11/22 23:32:01 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	int		time;
	int		j;

	i = 0;
	j = 0;
	if (error(ac, av))
	 	return (1);
	memset(&data, 0, sizeof(data));
	init_data(&data, av);
	init_philos(&data);
	while (data.philos[0].dead != 1)
	{
		i = 0;
		while (i < data.nb_philos)
		{
			j = 0;
			gettimeofday(&data.data_rightnow, NULL);
			time = data_time_rn(&data);
			pthread_mutex_lock(&data.philos[i].main_check);
			if (time > data.philos[i].eat_or_die 
				|| data.philos[j].meal_counter == 0)
			{
			
				pthread_mutex_unlock(&data.philos[i].main_check);
				j = 0;
				while (j < data.nb_philos)
				{
				
					pthread_mutex_lock(&data.philos[j].main_check);
					data.philos[j].dead = 1;
				//	pthread_mutex_lock(&data.print);
				//	printf("\t\t\tId : %d\tValue : %d\tAdress : %p\n", data.philos[j].id, data.philos[j].dead, &data.philos[j].dead);
				//	pthread_mutex_unlock(&data.print);
					pthread_mutex_unlock(&data.philos[j].main_check);

					j++;
				}
					
				//data.philos[i].dead = 1;
				pthread_mutex_unlock(&data.philos[i].main_check);
				pthread_mutex_lock(&data.print);
				pthread_mutex_lock(&data.philos[i].main_check);
				if (data.philos[0].meal_counter != 0)
					printf("%d %d has died!\n", time, data.philos[i].id);
				pthread_mutex_unlock(&data.philos[i].main_check);
				pthread_mutex_unlock(&data.print);
		
				break ;
			}
			pthread_mutex_unlock(&data.philos[i].main_check);
			i++;
		}
		
	}
	fin(&data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetre <apetre@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:49:19 by apetre            #+#    #+#             */
/*   Updated: 2024/01/14 04:49:19 by apetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				eat_or_die;
	int				meal_duration;
	int				sleeping_time;
	int				max_meals;
	short int		dead;
	short int		data_dead;
	struct timeval	genesis;
	struct timeval	data_rightnow;	
	t_philo			*philos;
	pthread_t		*reaper;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	print;
	pthread_mutex_t	check_rightnow;
	pthread_mutex_t	take_forks;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				temp_time;
	int				eat_or_die;
	int				meal_counter;
	short int		dead;
	struct timeval	rightnow;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	main_check;
	pthread_t		core;
	t_data			*data;
}					t_philo;

// INITIALIZATION //
void		init_data(t_data *data, char **av);
void		init_philos(t_data *data);

// ROUTINE //
void		*philo_routine(void *arg);

// PHILOSOHOPERS ACTIONS //
void		sleeping(t_philo *philo);
void		eating(t_philo *philo);
void		thinking(t_philo *philo);

// CHECK STATES //
int			time_rn(t_philo *philo);
int			data_time_rn(t_data *data);

int			check_this_philo_state(t_philo *philo);
int			check_if_any_died(t_philo *philo);

// TOOLS //
int			ft_atoi(const char *nptr);
size_t		ft_strlen_no_spaces(char *str);
size_t		count_size_in_chars(int n);
void		check_print(char *str, int time, t_philo *philo);
void		slumber(t_philo *philo, int endofwinter);

// END PROGRAM //
void		fin(t_data *data);
int			error(int ac, char **av);

#endif
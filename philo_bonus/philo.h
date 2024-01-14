#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <fcntl.h>
# include <signal.h>

typedef	struct s_philo s_philo;


typedef	struct s_data
{
	int					nb_philos;
	int					eat_or_die;
	int					meal_duration;
	int					sleeping_time;
	int					max_meals;
	int					finished_meals;
	struct	timeval		genesis;
	pid_t				*philos_ids;
	s_philo				*philos;
	sem_t				*forks_to_eat;
	sem_t				*stop;
	sem_t				*print;
	sem_t				*check_eat_or_die;
	sem_t				*take_forks;
	sem_t				*meal_counter;
	sem_t				check_time;
} 						t_data;

typedef	struct s_philo
{
	int					id;
	int					eat_or_die;
	int					meal_counter;
	int					temp_time;
	struct	timeval		philo_time;
	struct	timeval		thread_time;
	t_data				*data;
	pthread_t			reaper;

}						t_philo;

void	init_data(t_data *data, char **av);
void	init_philos(t_data *data);

void	child_routine(t_philo *philo);
void	*reaper_routine(void *arg);


// TOOLS //
int			ft_atoi(const char *nptr);
size_t		ft_strlen_no_spaces(char *str);
size_t		count_size_in_chars(int n);
void		check_print(char *str, int time, t_philo *philo);
int			time_rn_philo(t_philo *philo);
int			time_rn_thread(t_philo *philo);




void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	take_fork(t_philo *philo);
void	eating(t_philo *philo);

int	error(int ac, char **av);

#endif
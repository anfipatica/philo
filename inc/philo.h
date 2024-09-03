/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:54:28 by anfi              #+#    #+#             */
/*   Updated: 2024/09/03 20:28:09 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define STD "\033[0m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[1;36m"
# define ORANG "\033[1;33m"

// error definitions.
# define WRONG_ARGUMENT_NUMBER -1
# define NEGATIVE_NUMBER -2
# define INVALID_CHAR -3
# define INVALID_TIME -4
# define MALLOC_ERROR -5
# define PTHREAD_ERROR -6
# define ERROR_INT -7
# define TOO_MANY_PHILOS -8

typedef enum e_boolean
{
	false = 0,
	true = 1
}		t_bool;

typedef enum e_mutex_options
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_mutex;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FORK,
	DIED,
}			t_state;

typedef struct s_data
{
	pthread_t		monitor;
	uint64_t		start_time;
	uint64_t		death;
	uint64_t		eat;
	uint64_t		sleep;
	int				total_philos;
	int				min_meals;
	int				philos_full;
	pthread_mutex_t	philos_full_mutex;
	t_bool			all_alive;
	pthread_mutex_t	all_alive_mutex;
	t_bool			all_ate;
	pthread_mutex_t	all_ate_mutex;
	t_bool			all_ready;
	pthread_mutex_t	all_ready_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
}				t_data;

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_bool			state;
	t_bool			can_eat;
	int				times_eaten;
	struct s_philo	*target_philo;
	unsigned long	last_meal;
	pthread_mutex_t	last_meal_mutex;
	t_data			*data;
}				t_philo;

/* validation.c
Functions to validate the arguments received*/

int				validate_arguments(char **argv);
long			validate_argv(char *s);

/* init.c
	Functions to initialice the values inside the t_data and t_philo structs*/

void			assign_forks(t_philo *philo, pthread_mutex_t *forks, int i);
t_data			*init_data(int argc, char **argv);
t_philo			*init_philos(t_data *data, t_philo *philo);
void			init_mutex(t_data *data, t_philo *philo);

/*utils.c
	A couple of auxiliar util functions, some from the libft
	and other couple specifically made for this project.*/

void			*ft_calloc(size_t nitems, size_t size);
int				ft_atoi(const char *s);
unsigned long	get_time(void);
void			own_msleep(unsigned long milliseconds, t_data *data);
void			wait_all_threads(t_data *data);

/*philo.c
	Where the main is.
	Is also where the thread create function is, meaning it's the beginning
	of the dinner simulation.*/

int				dinner_start(t_data *data, t_philo *philo);
int				main(int argc, char **argv);

/*monitor.c
	The functions used by the monitoring thread to work
	and check the dinner status*/

t_bool			meal_continues(t_data *data);
void			*monitor_function(void *data_void);
t_bool			check_if_dead(t_philo *philo);

/* getters_setters.c
	A couple of short functions to safely check booleans
	in order to avoid data races.*/

void			set_bool(pthread_mutex_t *mutex, t_bool *bool, t_bool value);
t_bool			get_bool(pthread_mutex_t *mutex, t_bool *bool);

/* actions.c 
	The actions followed by our philosophers.*/

void			check_if_full(t_philo *philo, t_data *data);
void			*eat_one_philo(void *philo_voi);
void			eat(t_philo *philo, t_data *data);
void			*eat_sleep_repeat(void *philo_void);

/** print_funtions.c */

int				error_exit(int error);
void			print_status(t_state state, t_philo *philo);

/* free.c
*/

void			ft_free(t_philo *philo, t_data *data);

#endif
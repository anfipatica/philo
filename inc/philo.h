/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:54:28 by anfi              #+#    #+#             */
/*   Updated: 2024/08/14 23:36:37 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <string.h> //for memset
# include <sys/time.h>
# include <stdint.h>

typedef enum s_boolean
{
	false = 0,
	true = 1
}		t_bool;


typedef struct	s_data
{
	pthread_t	main_thread[1];
	uint64_t	start_time; //when the program starts.
	uint64_t	death; //how long before they die without food
	uint64_t	eat; //how long it takes them to eat.
	uint64_t	sleep; // how long it takes them to sleep.
	int	total_philos; //how many philos we start with.
	int	min_meals; // How many meals each philo needs to exit the program.
	int	philos_full; // how many philos have eaten as much as needed.
	t_bool	all_alive;
	t_bool	all_ate;
}				t_data;

typedef struct	s_philo
{
	int				index;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	t_bool			state;
	int				times_eaten;
	struct s_philo	*target_philo;
	unsigned long	last_meal;
	t_data			*data;
}				t_philo;

typedef struct	s_pack
{
	t_philo	*philo;
	t_data	*data;
}				t_pack;


/*utils.c
	A couple of util functions from libft, since libft is not allowed.
*/

void	*ft_calloc(size_t nitems, size_t size);
int		ft_atoi(const char *s);
unsigned long	get_time(void);


/* init.c

 */

void	init_philos(t_data *data, t_philo *philo);
void	init_data(t_data *data, t_philo *philo, char **argv, int argc);

/* free.c

*/

void	ft_free(t_philo *philo, t_data data);
int	free_threads(t_philo *philo, t_data *data);

#endif
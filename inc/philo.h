/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:54:28 by anfi              #+#    #+#             */
/*   Updated: 2024/08/06 23:57:07 by anfi             ###   ########.fr       */
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
typedef enum s_boolean
{
	false = 0,
	true = 1
}		t_bool;

typedef struct	s_philo
{
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	int				index;
	t_bool			state;
	int				times_eaten;
	struct s_philo	*left;
	struct s_philo	*right;
	unsigned long	*last_meal;
}				t_philo;

typedef struct	s_data
{
	int start_time; //when the program starts.
	int	death; //how long before they die without food
	int	eat; //how long it takes them to eat.
	int	sleep; // how long it takes them to sleep.
	int	total_philos; //how many philos we start with.
	int	min_meals; // How many meals each philo needs to exit the program.
	int	philos_full; // how many philos have eaten as much as needed.
}				t_data;

typedef struct	s_pack
{
	t_philo	*philo;
	t_data	*data;
}				t_pack;


/*utils.c
	A couple of util functions from libft, since libft is not allowed.
*/

void	*ft_calloc(size_t nitems, size_t size);
int		ft_isdigit(int c);
int		ft_atoi(const char *s);



#endif
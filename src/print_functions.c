/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:58:04 by anfi              #+#    #+#             */
/*   Updated: 2024/08/21 20:32:49 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_exit(const char *error)
{
	printf(RED"%s\n"STD, error);
	return (1);
}

// void	print_status(t_state state, t_philo *philo)
// {
// 	long	time;
// 	if (meal_continues(philo->data) == false)
// 	{
// 		return ;
// 	}
// 	pthread_mutex_lock(&philo->data->write_mutex);
// 	time = get_time() - philo->data->start_time;
// 	if (state == TAKE_FORK) // maybe add a checker to see if meal is over to every if else.
// 		printf("%ld %d has taken a fork\n", time, philo->index);
// 	else if (state == EATING)
// 		printf("%ld %d is eating\n", time, philo->index);
// 	else if (state == SLEEPING)
// 		printf("%ld %d is sleeping\n", time, philo->index);
// 	else if (state == THINKING)
// 		printf("%ld %d is thinking\n", time, philo->index);
// 	else if (state == DIED)
// 		printf("%ld %d died\n", time, philo->index);
// 	pthread_mutex_unlock(&philo->data->write_mutex);
	
// }

void	print_status(t_state state, t_philo *philo)
{
	long	time;
//	pthread_mutex_lock(&philo->data->write_mutex);
	if (meal_continues(philo->data) == false)
	{
//		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	time = get_time() - philo->data->start_time;
	if (state == TAKE_FORK) // maybe add a checker to see if meal is over to every if else.
		printf(PURPLE"%ld %d has taken a fork\n"STD, time, philo->index);
	else if (state == EATING)
		printf(GREEN"%ld %d is eating\n"STD, time, philo->index);
	else if (state == SLEEPING)
		printf(BLUE"%ld %d is sleeping\n"STD, time, philo->index);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", time, philo->index);
	else if (state == DIED)
		printf(RED"%ld %d died\n"STD, time, philo->index);
//	pthread_mutex_unlock(&philo->data->write_mutex);
	
}
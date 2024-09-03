/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:58:04 by anfi              #+#    #+#             */
/*   Updated: 2024/09/03 18:56:07 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_exit_two(int error)
{
	if (error == MALLOC_ERROR)
		printf(RED"*MALLOC_ERROR*\n"ORANG"Malloc failled allocating.\n"STD);
	else if (error == PTHREAD_ERROR)
		printf(RED"*PTHREAD_ERROR*\n"ORANG"Pthread failled.\n"STD);
	else if (error == ERROR_INT)
	{
		printf(RED"*ERROR_INT*\n"ORANG"Please, enter only positive"
		" numbers inside the int range.\n"STD);
	}
	else if (error == INVALID_TIME)
	{
		printf(RED"*INVALID_TIME*\n"ORANG"Please, enter times "
		"longer than 60 ms\n"STD);
	}
	else if (error == TOO_MANY_PHILOS)
	{
		printf(RED"*TOO_MANY_PHILOS*\n"ORANG"Please, don't enter more "
		"than 200 philos.\nThe pc might explode!!\n"STD);
	}
	return (1);
}

int	error_exit(int error)
{
	if (error == WRONG_ARGUMENT_NUMBER)
	{
		printf(RED"*WRONG_ARGUMENT_NUMBER*\n\n"
		"The program must be executed with the following arguments:\n\n"
		BLUE"./philo [nº_philosopers] [time_to_die] [time_to_eat] "
		"[time_to_sleep]\n   (optional: [nºtimes_each_philosopher"
		"_must_eat])\n"STD"\nExample: ./philo 4 400 210 100 5\n"
		RED"\nIt only accepts positive int values!!\n"STD);
	}
	else if (error == NEGATIVE_NUMBER)
	{
		printf(RED"*NEGATIVE_NUMBER*\n"
		ORANG"Please enter only positive ints\n"STD);
	}
	else if (error == INVALID_CHAR)
	{
		printf(RED"*INVALID_CHAR*\n"ORANG"Found an invalid char.\n"
		"Please enter only numeric values\n"STD);
	}
	else
		error_exit_two(error);
	return (1);
}

void	print_status(t_state state, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->write_mutex);
	if (meal_continues(philo->data) == false)
	{
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	time = get_time() - philo->data->start_time;
	if (state == TAKE_FORK)
		printf(PURPLE"%ld	%d has taken a fork\n"STD, time, philo->index);
	else if (state == EATING)
		printf(GREEN"%ld	%d is eating\n"STD, time, philo->index);
	else if (state == SLEEPING)
		printf(BLUE"%ld	%d is sleeping\n"STD, time, philo->index);
	else if (state == THINKING)
		printf("%ld	%d is thinking\n", time, philo->index);
	else if (state == DIED)
		printf(RED"%ld	%d died\n"STD, time, philo->index);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:11 by anfi              #+#    #+#             */
/*   Updated: 2024/09/18 19:23:28 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * A function to free all the dinamically allocated memory
 * and destroy the used mutexes.
 */
void	ft_free(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->all_alive_mutex);
	pthread_mutex_destroy(&data->all_ate_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->philos_full_mutex);
	while (++i < data->total_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
	}
	free(data->forks);
	free(philo);
	free(data);
}

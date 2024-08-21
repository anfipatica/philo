/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:11 by anfi              #+#    #+#             */
/*   Updated: 2024/08/21 18:07:11 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// int	free_threads(t_philo *philo, t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i != data->total_philos)
// 	{
// 		if (philo[i].philo)
// 		{
// 			pthread_join(*philo[i].philo, NULL);
// 			free(philo[i].philo);
// 		}
// 	}
// 	return (0);
// }

void	ft_free(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->total_meals_mutex);
	while (++i < data->total_philos)
	{
		// if (philo[i].thread)
		// 	pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_join(*data->monitor, NULL);
	free(philo);
	free(data->forks);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:11 by anfi              #+#    #+#             */
/*   Updated: 2024/08/20 22:49:16 by anfi             ###   ########.fr       */
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
	while (++i < data->total_philos)
	{
		philo[i].last_meal = data->start_time;
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_join(*data->monitor, NULL);
	free(philo);
	free(data->forks);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:11 by anfi              #+#    #+#             */
/*   Updated: 2024/09/02 20:07:59 by anfi             ###   ########.fr       */
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

// void	ft_free(t_philo *philo, t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	pthread_mutex_destroy(&data->data_);
// 	pthread_mutex_destroy(&data->write_mutex);
// 	pthread_mutex_destroy(&data->total_meals_mutex);
// 	while (++i < data->total_philos)
// 	{
// 		// if (philo[i].thread)
// 		// 	pthread_join(philo[i].thread, NULL);
// 		pthread_mutex_destroy(&data->forks[i]);
// 	}
// 	pthread_join(*data->monitor, NULL);
// 	free(philo);
// 	free(data->forks);
// }

void	ft_free(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	printf("LELELELEL\n\n");
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

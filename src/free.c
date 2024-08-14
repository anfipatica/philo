/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:11 by anfi              #+#    #+#             */
/*   Updated: 2024/08/14 23:42:42 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	free_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i != data->total_philos)
	{
		if (philo[i].philo)
		{
			pthread_join(*philo[i].philo, NULL);
			free(philo[i].philo);
		}
	}
	return (0);
}

void	ft_free(t_philo *philo, t_data data)
{
	int	i;

	i = -1;
	while (++i < data.total_philos)
	{
		printf("i = %d, fork = %p\n", i, philo[i].fork);
		if (philo[i].fork)
		{
			//pthread_detach(*philo[i].philo);
			pthread_mutex_destroy(philo[i].fork);
			free(philo[i].fork);
		}
	}
	free(philo);
}
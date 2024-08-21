/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:19:13 by anfi              #+#    #+#             */
/*   Updated: 2024/08/21 14:38:07 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *monitor_function(void *philo_void)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = (t_philo *)philo_void;
	data = (t_data *)philo[0].data;
	i = -1;
	wait_all_threads(data);
	while (meal_continues(data) == true)
	{
		++i;
		if (philo[i].last_meal == 0) //add a mutex
			philo[i].last_meal = get_time();
		if ((get_time() - philo[i].last_meal) > data->death) //maybe add a safer to way to access last_meal
		{
			printf("--> %lu\n", (get_time() - philo[i].last_meal));
			print_status(DIED, &philo[i]);
			set_bool(&data->data_mutex, &data->all_alive, false);
			break;
		}
		if (i + 1 >= data->total_philos)
			i = -1;
	}
	return (NULL);
}

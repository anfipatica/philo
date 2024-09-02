/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:19:13 by anfi              #+#    #+#             */
/*   Updated: 2024/09/02 23:02:42 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_data *data)
{
	while (get_bool(&data->all_ready_mutex, &data->all_ready) == false)
		;
}

t_bool	check_if_dead(t_philo *philo)
{
	t_bool	bool;

	bool = false;
	pthread_mutex_lock(&philo->last_meal_mutex);
	if ((get_time() - philo->last_meal) > philo->data->death)
		bool = true;
//	printf("%d----->%lu\n", philo->index, get_time() - philo->last_meal);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (bool);
}
void *monitor_function(void *philo_void)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = (t_philo *)philo_void;
	data = (t_data *)philo[0].data;
	wait_all_threads(data);
	printf("threads listos!!\n");
	precise_usleep(data->death / 2, data);
	i = 0;
	while (meal_continues(data) == true)
	{
		if (check_if_dead(&philo[i]) == true)
		{
			print_status(DIED, &philo[i]);
			set_bool(&data->all_alive_mutex, &data->all_alive, false);
			return (NULL);
		}
		if (++i >= data->total_philos)
			i = 0;
	}
	return (NULL);
}

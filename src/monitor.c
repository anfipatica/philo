/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:19:13 by anfi              #+#    #+#             */
/*   Updated: 2024/09/18 16:53:06 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**A function to safely check both needed booleans to keep the dinner running*/
t_bool	meal_continues(t_data *data)
{
	if (get_bool(&data->all_alive_mutex, &data->all_alive) == false)
		return (false);
	if (get_bool(&data->all_ate_mutex, &data->all_ate) == true)
		return (false);
	return (true);
}

/**This function will check if the sent philo is alive.
 * If it has been longer than the received death time since the last
 * time they *finished* eating, they are dead.*/
t_bool	check_if_dead(t_philo *philo)
{
	t_bool	bool;

	bool = false;
	pthread_mutex_lock(&philo->last_meal_mutex);
	if ((get_time() - philo->last_meal) > philo->data->death)
		bool = true;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (bool);
}

/**The monitor itself. A thread that will run paralel to the philosophers and
 * the main thread checking the state of the dinner, ending it whenever any
 * philosopher dies or the minimum meal request has been achieved.*/
void	*monitor_function(void *philo_void)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = (t_philo *)philo_void;
	data = (t_data *)philo[0].data;
	own_msleep(data->death / 2, data);
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

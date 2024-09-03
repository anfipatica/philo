/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:19:13 by anfi              #+#    #+#             */
/*   Updated: 2024/09/03 20:46:11 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * This function will increase a counter each time its philo has eaten. When the
 * minimum meals requisement has been fulfilled, it will increase the
 * philos_full counter*/
void	check_if_full(t_philo *philo, t_data *data)
{
	if (data->min_meals > 0)
		philo->times_eaten++;
	if (data->min_meals > 0 && philo->times_eaten == data->min_meals)
	{
		pthread_mutex_lock(&data->philos_full_mutex);
		data->philos_full++;
		if (data->philos_full == data->total_philos)
			set_bool(&data->all_ate_mutex, &data->all_ate, true);
		pthread_mutex_unlock(&data->philos_full_mutex);
	}
}

/**This function represents the eating itself.
 * It first waits until it can pick up two forks, then it will
 * "eat", change it's last meal time and release both forks.
 */
void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKE_FORK, philo);
	pthread_mutex_lock(philo->second_fork);
	print_status(TAKE_FORK, philo);
	print_status(EATING, philo);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	own_msleep(data->eat, data);
	check_if_full(philo, data);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

/**A function that is called when there is only one philo*/
void	*eat_one_philo(void *philo_void)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_void;
	data = philo->data;
	wait_all_threads(data);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = data->start_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKE_FORK, philo);
	while (meal_continues(data))
		own_msleep(200, data);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}

/**The dinner simulation iself.
 * It will keep running until any philosopher dies or the minimum meals
 * have been reached*/
void	*eat_sleep_repeat(void *philo_void)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_void;
	data = philo->data;
	wait_all_threads(data);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = data->start_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	while (meal_continues(data))
	{
		eat(philo, data);
		print_status(SLEEPING, philo);
		own_msleep(data->sleep, data);
		print_status(THINKING, philo);
		own_msleep(1, data);
	}
	return (NULL);
}

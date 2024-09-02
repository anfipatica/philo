/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:19:13 by anfi              #+#    #+#             */
/*   Updated: 2024/09/02 23:04:59 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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


void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKE_FORK, philo);
	pthread_mutex_lock(philo->second_fork);
	print_status(TAKE_FORK, philo);
	
	print_status(EATING, philo);
	precise_usleep(data->eat, data);
	
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);

	check_if_full(philo, data);

	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	*eat_one_philo(void *philo_void)
{
	t_philo	*philo;
	t_data *data;

	philo = (t_philo *)philo_void;
	data = philo->data;
	wait_all_threads(data);
	printf("comenzamos!\n");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = data->start_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKE_FORK, philo);
	while (meal_continues(data))
		precise_usleep(200, data);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}


void	*eat_sleep_repeat(void *philo_void)
{
	t_philo	*philo;
	t_data *data;

	philo = (t_philo *)philo_void;
	data = philo->data;
	wait_all_threads(data);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = data->start_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	while (get_bool(&data->all_alive_mutex, &data->all_alive) == true &&
		get_bool(&data->all_ate_mutex, &data->all_ate) == false)
	{
		eat(philo, data);
		print_status(SLEEPING, philo);
		precise_usleep(data->sleep, data);
		print_status(THINKING, philo);
	}
	return (NULL);
}

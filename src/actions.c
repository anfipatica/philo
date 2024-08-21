/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:19:13 by anfi              #+#    #+#             */
/*   Updated: 2024/08/21 20:53:37 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_data *data)
{
	while (get_bool(&data->data_mutex, &data->all_ready) == false)
		;
}

void	check_if_full(t_philo *philo, t_data *data)
{
	if (data->min_meals > 0)
		philo->times_eaten++;
	pthread_mutex_lock(&data->total_meals_mutex);
	if (data->philo_feed == data->total_philos)
		data->philo_feed = 0;
	data->philo_feed++;
	if (data->min_meals > 0 && philo->times_eaten == data->min_meals)
	{
		data->philos_full++;
		pthread_mutex_lock(&data->write_mutex);
		if (data->philos_full == data->total_philos)
		{
			set_bool(&data->data_mutex, &data->all_ate, true);
		}
		pthread_mutex_unlock(&data->write_mutex);
	}
	pthread_mutex_unlock(&data->total_meals_mutex);
}


void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKE_FORK, philo);
	pthread_mutex_lock(philo->second_fork);
	print_status(TAKE_FORK, philo);
	philo->last_meal = get_time();
	print_status(EATING, philo);
	precise_usleep(data->eat, data);
	check_if_full(philo, data);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	eat_one_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKE_FORK, philo);
	while (meal_continues(data))
		precise_usleep(200, data);
}


void	*eat_sleep_repeat(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	wait_all_threads(philo->data);
	if (philo->data->total_philos == 1)
	{
		eat_one_philo(philo, philo->data);
		return NULL;
	}
	while (meal_continues(philo->data) == true)
	{	if (philo->can_eat == true)
		{
			eat(philo, philo->data);
			print_status(SLEEPING, philo);
			precise_usleep(philo->data->sleep, philo->data);
			print_status(THINKING, philo);
			philo->can_eat = false;
		}
		pthread_mutex_lock(&philo->data->total_meals_mutex);
		if (philo->data->philo_feed == philo->data->total_philos)
			philo->can_eat = true;
		pthread_mutex_unlock(&philo->data->total_meals_mutex);

	}
	return (NULL);
}


void	dinner_start(t_data *data, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < data->total_philos)
	{
		pthread_create(&philo[i].thread, NULL, eat_sleep_repeat, &philo[i]);
	}
	pthread_create(data->monitor, NULL, monitor_function, philo);
	set_bool(&data->data_mutex, &data->all_ready, true);
	data->start_time = get_time();
	i = -1;
	while (++i < data->total_philos)
	{
		philo[i].last_meal = data->start_time;
		pthread_join(philo[i].thread, NULL);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:19:13 by anfi              #+#    #+#             */
/*   Updated: 2024/08/20 22:33:08 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_state state, t_philo *philo)
{
	long	time;
	if (meal_continues(philo->data) == false)
	{
		return ;
	}
	pthread_mutex_lock(&philo->data->write_mutex);
	time = get_time() - philo->data->start_time;
	if (state == TAKE_FORK) // maybe add a checker to see if meal is over to every if else.
		printf("%ld %d has taken a fork\n", time, philo->index);
	else if (state == EATING)
		printf(GREEN"%ld %d is eating\n"STD, time, philo->index);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->index);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", time, philo->index);
	else if (state == DIED)
		printf(RED"%ld %d died\n"STD, time, philo->index);
	pthread_mutex_unlock(&philo->data->write_mutex);
	
}

void	wait_all_threads(t_data *data)
{
	while (get_bool(&data->data_mutex, &data->all_ready) == false)
		;
}

void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKE_FORK, philo);
	pthread_mutex_lock(philo->second_fork);
	print_status(TAKE_FORK, philo);

	print_status(EATING, philo);
	precise_usleep(data->eat, data);
	philo->last_meal = get_time();
	if (data->min_meals > 0)
		philo->times_eaten++;
	if (data->min_meals > 0 && philo->times_eaten == data->min_meals)
	{
		set_int(&data->data_mutex, &data->philos_full, data->philos_full + 1); //maybe another mutex is needed???
		if (get_int(&data->data_mutex, &data->philos_full) == data->total_philos)
			set_bool(&data->data_mutex, &data->all_ate, true);
	}
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	eat_one_philo(t_philo *philo, t_data *data)
{
	printf("one lonely boy\n");
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKE_FORK, philo);
	while (meal_continues(data))
		precise_usleep(200, data);
}


void	*dinner_simulation(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	wait_all_threads(philo->data);
	printf("ready!! %d\n", philo->index);
	if (philo->data->total_philos == 1)
	{
		eat_one_philo(philo, philo->data);
		return NULL;
	}
	while (meal_continues(philo->data) == true)
	{
		eat(philo, philo->data);
		print_status(SLEEPING, philo);
		precise_usleep(philo->data->sleep, philo->data);
		print_status(THINKING, philo);
	}
	return (NULL);
}


void	dinner_start(t_data *data, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < data->total_philos)
	{
		pthread_create(&philo[i].thread, NULL, dinner_simulation, &philo[i]);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:13:38 by anfi              #+#    #+#             */
/*   Updated: 2024/09/02 22:14:35 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	//if there is only one philo could this lead to problems??? aparently not but ????
	if (philo->index % 2)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo->data->total_philos];
	}
	else
	{
		philo->first_fork = &forks[(i + 1) % philo->data->total_philos];
		philo->second_fork = &forks[i];
	}

}

t_philo	*init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	philo = ft_calloc(data->total_philos, sizeof(t_philo));
	if (!philo)
		return (free(data->forks), free(data), NULL);
	while (++i < data->total_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		philo[i].last_meal = 0;
		philo[i].times_eaten = 0;
		philo[i].index = i + 1;
		philo[i].data = data;

		if (i + 1 == data->total_philos)
			philo[i].target_philo = &philo[0];
		else
			philo[i].target_philo = &philo[i + 1];
		philo[i].data = data;
		assign_forks(&philo[i], data->forks, i);
		philo[i].can_eat = true;
	}
	return (philo);
}
t_data	*init_data(int argc, char **argv)
{
	t_data *data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->total_philos = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	else
		data->min_meals = -1;
	data->all_alive = true;
	data->all_ate = false;
	data->all_ready = false;
	data->philos_full = 0;
	data->forks = ft_calloc(data->total_philos, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (free(data), NULL);
//	data->philo_feed = 0;
	pthread_mutex_init(&data->all_alive_mutex, NULL);
	pthread_mutex_init(&data->all_ate_mutex, NULL);
	pthread_mutex_init(&data->all_ready_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->philos_full_mutex, NULL);
	return (data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:13:38 by anfi              #+#    #+#             */
/*   Updated: 2024/08/14 23:23:23 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * This function inits the data values needed inside t_data and t_philo,
 * and also, if it's been given, how many data a philo needs
 * to eat to finish the program.
 */

void	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->total_philos)
	{
		philo[i].last_meal = 0;
		philo[i].fork = ft_calloc(2, sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].fork, NULL);
		philo[i].index = i + 1;
		if (i + 1 == data->total_philos)
			philo[i].target_philo = &philo[0];
		else
			philo[i].target_philo = &philo[i + 1];
		philo[i].data = data;
	}
}
void	init_data(t_data *data, t_philo *philo, char **argv, int argc)
{
	data->total_philos = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]) * 1000;
	data->sleep = ft_atoi(argv[4]) * 1000;
	data->philos_full = 0;
	data->all_alive = true;
	data->all_ate = false;
	data->start_time = get_time();
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	else
		data->min_meals = -1;
	init_philos(data, philo);
}

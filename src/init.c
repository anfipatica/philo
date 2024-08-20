/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:13:38 by anfi              #+#    #+#             */
/*   Updated: 2024/08/20 22:38:14 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	if (philo->index % 2 || philo->index == 0)
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
	data->forks = ft_calloc(data->total_philos, sizeof(pthread_mutex_t));
	while (++i < data->total_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
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
	}
	printf("philo[0] index = %d\n", philo[0].index);
	return (philo);
}
void	init_data(t_data *data, int argc, char **argv)
{
	data->total_philos = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	else
		data->min_meals = -1;
	if (data->death < 6e4 || data->eat < 6e4 || data->sleep < 6e4)
		error_exit("Please, use times bigger than 60ms");
	data->all_alive = true;
	data->all_ate = false;
	data->all_ready = false;
	data->philos_full = 0;
	pthread_mutex_init(&data->data_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
}

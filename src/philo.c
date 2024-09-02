/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:55:37 by anfi              #+#    #+#             */
/*   Updated: 2024/09/02 22:26:53 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// n_philosophers, data_to_die, data_to_eat, data_to_sleep, [number_of_data_each_philo_must_eat]

int	dinner_start(t_data *data, t_philo *philo)
{
	int	i;

	if (pthread_create(&data->monitor, NULL, monitor_function, philo))
		return (error_exit(PTHREAD_ERROR));
	pthread_detach(data->monitor);
	i = -1;
	while (++i < data->total_philos)
	{
		if (data->total_philos == 1)
		{
			printf("Vaya! una unidad de filósofo\n");
			pthread_create(&philo[i].thread, NULL, eat_one_philo, &philo[i]);
			printf("break!!!\n");
			break;
		}
		pthread_create(&philo[i].thread, NULL, eat_sleep_repeat, &philo[i]);
	}
	data->start_time = get_time();
	printf("->star_time here is: %lu\n", data->start_time);
	set_bool(&data->all_ready_mutex, &data->all_ready, true);
	i = -1;
	while (++i < data->total_philos)
		pthread_join(philo[i].thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philos;
	
	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		if (validate_arguments(argv))
			return (1);
		data = init_data(argc, argv);
		if (!data)
			return (error_exit(MALLOC_ERROR));
		philos = init_philos(data, philos);
		if (!philos)
			return (error_exit(MALLOC_ERROR));
		dinner_start(data, philos);
		ft_free(philos, data);
	}
	else
		return (error_exit(WRONG_ARGUMENT_NUMBER));
	return (0);
}

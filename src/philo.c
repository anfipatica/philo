/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:55:37 by anfi              #+#    #+#             */
/*   Updated: 2024/08/20 22:30:44 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// n_philosophers, data_to_die, data_to_eat, data_to_sleep, [number_of_data_each_philo_must_eat]


int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	
	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		if (validate_arguments(argc, argv) == false)
			return (error_exit("Found at least one non numeric char"), 1);
		init_data(&data, argc, argv);
		philos = init_philos(&data, philos);
		printf("--philo[0] index = %d\n", philos[0].index);
		dinner_start(&data, philos);
		ft_free(philos, &data);
	}
	else
		return (error_exit("Wrong input. You need to send 5 or 6 int arguments"), 1);
	return (0);
}

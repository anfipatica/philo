/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:55:37 by anfi              #+#    #+#             */
/*   Updated: 2024/08/21 17:01:19 by ymunoz-m         ###   ########.fr       */
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
		if (validate_arguments(argv))
			return (1);
		if (init_data(&data, argc, argv))
			return (error_exit("Please, use times bigger than 60ms"));
		philos = init_philos(&data, philos);
		dinner_start(&data, philos);
		printf("SANSEACABÓ!\n");
		ft_free(philos, &data);
	}
	else
		return (error_exit("Wrong input. You need to send 5 or 6 int arguments"));
	return (0);
}

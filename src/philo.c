/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:55:37 by anfi              #+#    #+#             */
/*   Updated: 2024/08/07 00:03:13 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// n_philosophers, data_to_die, data_to_eat, data_to_sleep, [number_of_data_each_philo_must_eat]

unsigned long get_data(void)
{
	struct timeval time;
	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	validate_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (false);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (false);
		}
	}
	return (true);
}

/**
 * This function inits the data values needed inside t_data and t_philo,
 * and also, if it's been given, how many data a philo needs
 * to eat to finish the program.
 */
void	init_data(t_data *data, t_philo *philo, char **argv, int argc)
{
	int	i;

	i = -1;
	data->total_philos = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	data->philos_full = 0;
	while (++i < data->total_philos)
	{
		philo[i].last_meal = 0;
		philo[i].fork = ft_calloc(2, sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].fork, NULL);
		philo[i].index = i + 1;
	}
	printf("lel\n");
	i = -1;
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	else
		data->min_meals = -1;
}

void	*eat_sleep_repeat(void *pack_void)
{
	t_philo	*philo;
	t_data	*data;

	printf("OOOOOOOOOOOOOOOOO %p\n", pack_void);
	philo = ((t_pack *)pack_void)->philo;
	data = ((t_pack *)pack_void)->data;
	if (!pthread_mutex_lock(philo->fork))
	{
		printf("Hola!\n");
		printf("Philo %d is eating...%d\n", philo->index, data->min_meals);
		philo->times_eaten += 1;
		if (data->min_meals != -1 && philo->times_eaten == data->min_meals)
		{
			printf("ESTOY ACA!!\n");
			data->philos_full++;
		}
		usleep(data->eat);
		pthread_mutex_unlock(philo->fork);
	}
	else
		printf("Philo %d is thinking...\n", philo->index);
	return (NULL);
}

int	init_cicle(t_philo *philo, t_data *data)
{
	t_bool	all_alive;
	t_bool	all_ate;
	t_pack	pack[1];
	int i;

	i = 0;
	all_alive = true;
	all_ate = false;
	pack[0].data = data;
	while (all_alive == true && all_ate == false)
	{
		printf("LLEGAMOS ACÁ i = %d, total = %d\n", i, data->total_philos);
		if (i == data->total_philos)
		{
			i = -1;
			while (++i != data->total_philos)
			{
				pthread_join(*philo[i].philo, NULL);
				free(philo[i].philo);
			}
			i = 0;
		}
		pack[0].philo = &philo[i];
		philo[i].philo = ft_calloc(2, sizeof(pthread_t));
		pthread_create(philo[i].philo, NULL, eat_sleep_repeat, pack);
		i++;
		if (data->philos_full == data->total_philos)
		{
			all_ate = false;
			printf("COMIERON TODOS MI PANA!!!\n");
		}
	}
	return (0);
}

void	ft_free(t_philo *philo, t_data data)
{
	int	i;

	i = -1;
	while (++i < data.total_philos)
	{
		pthread_mutex_destroy(philo[i].fork);
		free(philo[i].fork);
		// if (philo[i].philo)
		// 	pthread_join(*philo[i].philo, NULL);
	}
	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;
	
	
	if (validate_arguments(argc, argv) == false)
		return (1);
	philo = ft_calloc(ft_atoi(argv[1]) + 1,sizeof(t_philo));

	if (!philo)
		return (1);
	init_data(&data, philo, argv, argc);
	init_cicle(philo, &data);
	ft_free(philo, data);
	return (0);
}

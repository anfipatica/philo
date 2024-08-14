/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:55:37 by anfi              #+#    #+#             */
/*   Updated: 2024/08/14 23:44:00 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// n_philosophers, data_to_die, data_to_eat, data_to_sleep, [number_of_data_each_philo_must_eat]

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


void	catch_forks(t_philo *philo, t_data *data)
{
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->fork);
	else
		pthread_mutex_lock(philo->target_philo->fork);
	printf("%lu %d has taken a fork\n", get_time() - data->start_time, philo->index);
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->target_philo->fork);
	else
		pthread_mutex_lock(philo->fork);
	printf("%lu %d has taken a fork\n", get_time() - data->start_time, philo->index);
}
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->target_philo->fork);
}
void	eat(t_philo *philo, t_data *data)
{
	printf("%lu %d is eating\n", get_time() - data->start_time, philo->index);
	philo->times_eaten += 1;
	if (data->min_meals != -1 && philo->times_eaten == data->min_meals)
	{
		data->philos_full++;
	}
	if (data->philos_full == data->total_philos)
		data->all_ate = true;
	usleep(data->eat);
}

void	*eat_sleep_repeat(void *philo_void)
{
	t_philo	*philo;

	philo = philo_void;
	while (philo->data->all_alive == true && philo->data->all_ate == false)
	{
		catch_forks(philo, philo->data);
		printf("EATS  > %lu\n", get_time());
		eat(philo, philo->data);
		drop_forks(philo);
		if (philo->data->all_alive != true || philo->data->all_ate != false)
			break;
		printf("SLEEPS> %lu\n", get_time());
		printf("%lu %d is sleeping\n", get_time() - philo->data->start_time, philo->index);
		usleep(philo->data->sleep);
	}
	return (NULL);
}

void	*check_philos_are_alive(void *philo_void)
{
	t_philo	*philo;
	t_data	*data;

	int		i;
	philo = (t_philo *)philo_void;
	data = (t_data *)philo[0].data;
	i = 0;
	while (data->all_alive == true)
	{
		if (i < data->total_philos)
			i = 0;
//		printf("i = %d, time = %lu, max_time = %lu\n", i, (get_time() - data->start_time) - philo[i].last_meal, data->death);
		if ((get_time() - data->start_time) - philo[i].last_meal >= data->death)
		{
			printf("%lu %d died\n", get_time() - philo->data->start_time, philo[i].index);
			data->all_alive = false;
			free_threads(philo, data);
		}
		i++;
		usleep(1000);
	}
	return (NULL);
}
int	init_threads(t_philo *philo, t_data *data)
{
	int i;

	i = -1;
	
	pthread_create(data->main_thread, NULL, check_philos_are_alive, philo);
	while (++i < data->total_philos)
	{
		philo[i].philo = ft_calloc(2, sizeof(pthread_t));
		pthread_create(philo[i].philo, NULL, eat_sleep_repeat, &philo[i]);
	}
	free_threads(philo, data);
	return (0);
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
	init_threads(philo, &data);
	printf("a liberar mi pana\n");
	ft_free(philo, data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:13:38 by anfi              #+#    #+#             */
/*   Updated: 2024/09/02 22:41:22 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_bool(pthread_mutex_t *mutex, t_bool *bool, t_bool value)
{
	pthread_mutex_lock(mutex);
	*bool = value;
	pthread_mutex_unlock(mutex);
}

t_bool	get_bool(pthread_mutex_t *mutex, t_bool *bool)
{
	t_bool ret;
	pthread_mutex_lock(mutex);
	ret = *bool;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

t_bool	meal_continues(t_data *data)
{
	if (get_bool(&data->all_alive_mutex, &data->all_alive) == false)
		return (false);
	if (get_bool(&data->all_ate_mutex, &data->all_ate) == true)
		return (false);
	return (true);
}

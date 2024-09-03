/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:13:38 by anfi              #+#    #+#             */
/*   Updated: 2024/09/03 18:50:00 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** This function changes the value of the specified boolean by the specified
 * value, with the protection of its respective mutex*/
void	set_bool(pthread_mutex_t *mutex, t_bool *bool, t_bool value)
{
	pthread_mutex_lock(mutex);
	*bool = value;
	pthread_mutex_unlock(mutex);
}

/** This function returns the value of the specified boolean
 * with the protection of its respective mutex*/
t_bool	get_bool(pthread_mutex_t *mutex, t_bool *bool)
{
	t_bool	ret;

	pthread_mutex_lock(mutex);
	ret = *bool;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:58:04 by anfi              #+#    #+#             */
/*   Updated: 2024/09/03 18:50:04 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *s)
{
	int	n;
	int	i;
	int	j;

	n = 0;
	i = 0;
	j = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+' )
	{
		if (s[i] == '-')
			j = j * -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = (n * 10) + (s[i] - '0');
		i++;
	}
	return (n * j);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*str;

	str = (malloc(nitems * size));
	if (str == 0)
		return (error_exit(MALLOC_ERROR), NULL);
	memset(str, '\0', size);
	return (str);
}

/**A function that returns in *milliseconds* the time since the Epoch
 */
unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

/**A more precise version of usleep, better for longer
 * periods of sleeping time
 * 
 * It also works in milliseconds instead of microseconds!!*/
void	own_msleep(unsigned long milliseconds, t_data *data)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < milliseconds)
	{
		if (meal_continues(data) == false)
			break ;
		usleep(500);
	}
}

/** This functions keeps the calling thread waiting until all threads
 * have been created, moment in which the all_ready boolean
 * will change its state.*/
void	wait_all_threads(t_data *data)
{
	while (get_bool(&data->all_ready_mutex, &data->all_ready) == false)
		;
}

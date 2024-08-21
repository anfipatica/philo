/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:58:04 by anfi              #+#    #+#             */
/*   Updated: 2024/08/21 14:33:09 by ymunoz-m         ###   ########.fr       */
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
		return (error_exit("Malloc error"), NULL);
	memset(str, '\0', size);
	return (str);
}

// void	handle_mutex_error(int status, t_mutex mutex_option)
// {
// 	if (status == 0)
// 		return ;
// 	if (status == EINVAL && mutex_option == LOCK || mutex_option == UNLOCK)
// 		error_exit("the mutex has not been properly initialized");
	
// }

// void	safe_mutex_handle(pthread_mutex_t *mutex, t_mutex mutex_option)
// {
// 	if (mutex_option == LOCK)
// 		handle_mutex_error(pthread_mutex_lock(mutex), mutex_option);
// 	else if (mutex_option == UNLOCK)
// 		handle_mutex_error(pthread_mutex_unlock(mutex), mutex_option);
// 	else if (mutex_option == INIT)
// 		handle_mutex_error(pthread_mutex_init(mutex, NULL), mutex_option);
// 	else if (mutex_option == DESTROY)
// 		handle_mutex_error(pthread_mutex_destroy(mutex), mutex_option);
// 	else
// 		error_exit("Invalid mutex option");
// }

unsigned long get_time(void)
{
	struct timeval time;
	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	precise_usleep(unsigned long milliseconds, t_data *data)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < milliseconds)
	{
		if (meal_continues(data) == false)
			break;
		usleep(500);
	}
}
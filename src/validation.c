/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:24:27 by anfi              #+#    #+#             */
/*   Updated: 2024/09/03 17:52:43 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	validate_argv(char *s)
{
	long	n;
	int		j;

	n = 0;
	j = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+' )
	{
		if (*s == '-')
			j = j * -1;
		s++;
	}
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (INVALID_CHAR);
		n = (n * 10) + (*s - '0');
		s++;
	}
	if (j == -1 && n != 0)
		return (NEGATIVE_NUMBER);
	else if (j == -1)
		return (INVALID_CHAR);
	return (n);
}

int	validate_arguments(char **argv)
{
	int		i;
	long	returned;

	i = 0;
	returned = 0;
	while (argv[++i])
	{
		returned = validate_argv(argv[i]);
		if (returned < 0)
			return (error_exit(returned));
		else if (returned > INT_MAX || returned < INT_MIN)
			return (error_exit(ERROR_INT));
		else if (i == 1 && returned > 200)
			return (error_exit(TOO_MANY_PHILOS));
		else if (i > 1 && i < 5 && returned < 60)
			return (error_exit(INVALID_TIME));
	}
	return (0);
}

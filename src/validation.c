/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:24:27 by anfi              #+#    #+#             */
/*   Updated: 2024/09/02 14:37:23 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	validate_argv(char *argv)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (argv[i])
	{
		while (argv[i] == ' ')
			i++;
		if (argv[i] && argv[i] == '+')
			i++;
		else if (argv[i] && argv[i] == '-')
			return (NEGATIVE_NUMBER);
		if (argv[i] && (argv[i] == '0' || (argv[i] < '0' || argv[i] > '9')))
			return (INVALID_CHAR);
		while (argv[i] && (argv[i] >= '0' && argv[i] <= '9'))
		{
			i++;
			if (!argv[i] || (argv[i] && argv[i] == ' '))
				n++;
			else if (argv[i] < '0' || argv[i] > '9')
				return (INVALID_CHAR);
		}
	}
	return (n);
}

int	validate_arguments(char **argv)
{
	int	i;
	int	returned;

	i = 0;
	returned = 0;
	while (argv[++i])
	{
		returned = validate_argv(argv[i]);
		if (returned < 0)
			return (error_exit(returned));
	}
	return (0);
}

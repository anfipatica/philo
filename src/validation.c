/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:24:27 by anfi              #+#    #+#             */
/*   Updated: 2024/08/21 14:28:48 by ymunoz-m         ###   ########.fr       */
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
			return (-2);
		if (argv[i] && (argv[i] == '0' || (argv[i] < '0' || argv[i] > '9')))
			return (-1);
		while (argv[i] && (argv[i] >= '0' && argv[i] <= '9'))
		{
			i++;
			if (!argv[i] || (argv[i] && argv[i] == ' '))
				n++;
			else if (argv[i] < '0' || argv[i] > '9')
				return (-1);
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
		if (returned == -2)
			return (error_exit("Please, enter only positive numbers"));
		else if (returned == -1)
			return (error_exit("Please, enter numeric values"));
	}
	return (0);
}

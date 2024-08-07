/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:58:04 by anfi              #+#    #+#             */
/*   Updated: 2024/08/06 14:11:51 by anfi             ###   ########.fr       */
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
		return (NULL);
	memset(str, '\0', size);
	return (str);
}
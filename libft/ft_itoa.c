/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:34:40 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/03 19:59:30 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	allocation(int n, char **res)
{
	int			i;
	long int	temp;

	i = 1;
	temp = n;
	if (temp < 0)
	{
		i++;
		temp *= -1;
	}
	else if (temp == 0)
		i++;
	while (temp > 0)
	{
		temp /= 10;
		i++;
	}
	*res = (char *)malloc(sizeof(char) * i);
	return (i - 1);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			i;
	long int	temp;

	i = allocation(n, &res);
	if (res == NULL)
		return (NULL);
	temp = n;
	if (n < 0)
	{
		temp *= -1;
		res[0] = '-';
	}
	res[i--] = '\0';
	if (temp == 0)
		res[i] = '0';
	while (temp > 0)
	{
		res[i--] = (temp % 10) + '0';
		temp /= 10;
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:36:22 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/13 07:18:11 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	get_offset(t_line *lst, int *offset)
{
	if (lst->x0 < *offset)
		*offset = lst->x0;
	if (lst->x1 < *offset)
		*offset = lst->x1;
	if (lst->y0 < *offset)
		*offset = lst->y0;
	if (lst->y1 < *offset)
		*offset = lst->y1;
}

int	get_point(int x, int y, int z, int is_x)
{
	int	res;

	res = 0;
	if (is_x)
		res = x - y;
	else
		res = ((x + y) / 2) - z;
	return (res);
}

float	get_scale(t_line *lst)
{
	float	scale;

	scale = 1;
	while (lst)
	{
		while (scale && lst->x0 * scale >= WIDTH - 20)
			scale -= 0.0005;
		while (scale && lst->x1 * scale >= WIDTH - 20)
			scale -= 0.0005;
		while (scale && lst->y0 * scale >= HEIGHT - 30)
			scale -= 0.0005;
		while (scale && lst->y1 * scale >= HEIGHT - 30)
			scale -= 0.0005;
		lst = lst->next;
	}
	return (scale);
}

t_height	min_max_height(t_line *res)
{
	t_height	height;

	height.min = 0;
	height.max = 0;
	while (res)
	{
		if (res->z0 < height.min)
			height.min = res->z0;
		if (res->z1 < height.min)
			height.min = res->z1;
		if (res->z0 > height.max)
			height.max = res->z0;
		if (res->z1 > height.max)
			height.max = res->z1;
		res = res->next;
	}
	return (height);
}

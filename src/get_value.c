/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:36:22 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/17 21:32:49 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	get_bounds(t_line *lst, t_height *x, t_height *y)
{
	x->min = INT_MAX;
	y->min = INT_MAX;
	x->max = INT_MIN;
	y->max = INT_MIN;
	while (lst)
	{
		x->min = fmin(fmin(x->min, lst->x0), lst->x1);
		x->max = fmax(fmax(x->max, lst->x0), lst->x1);
		y->min = fmin(fmin(y->min, lst->y0), lst->y1);
		y->max = fmax(fmax(y->max, lst->y0), lst->y1);
		lst = lst->next;
	}
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
	int		borders_x;
	int		borders_y;

	scale = 1;
	borders_x = (WIDTH / 2) - WIDTH / 30;
	borders_y = (HEIGHT / 2) - HEIGHT / 30;
	while (lst)
	{
		while (fabs((float)lst->x0 * scale) >= borders_x)
			scale -= 0.0005;
		while (fabs((float)lst->x1 * scale) >= borders_x)
			scale -= 0.0005;
		while (fabs((float)lst->y0 * scale) >= borders_y)
			scale -= 0.0005;
		while (fabs((float)lst->y1 * scale) >= borders_y)
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

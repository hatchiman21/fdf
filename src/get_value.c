/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:36:22 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/20 15:05:23 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	get_color(int height, int min_h, int max_h)
{
	int	normalized;
	int	red;
	int	green;
	int	blue;

	if (max_h != min_h)
		normalized = (height - min_h) * 255 / (max_h - min_h);
	else
		normalized = 255;
	if (normalized < 128)
	{
		red = 0;
		green = normalized * 2;
		blue = 255 - green;
	}
	else
	{
		red = (normalized - 128) * 2;
		green = 255 - red;
		blue = 0;
	}
	return ((red << 16) | (green << 8) | blue);
}

void	get_bounds(t_point **map, t_height *x_h, t_height *y_h, t_var *var)
{
	int		i;
	int		j;

	x_h->min = INT_MAX;
	y_h->min = INT_MAX;
	x_h->max = INT_MIN;
	y_h->max = INT_MIN;
	i = 0;
	while (i < var->rows)
	{
		j = 0;
		while (j < var->cols)
		{
			if (map[i][j].x < x_h->min)
				x_h->min = map[i][j].x;
			if (map[i][j].x > x_h->max)
				x_h->max = map[i][j].x;
			if (map[i][j].y < y_h->min)
				y_h->min = map[i][j].y;
			if (map[i][j].y > y_h->max)
				y_h->max = map[i][j].y;
			j++;
		}
		i++;
	}
}

void	get_scale(t_point **map, t_var *var)
{
	int		i;
	int		j;
	int		borders_x;
	int		borders_y;

	var->scale = 1;
	borders_x = (WIDTH / 2) - WIDTH / 30;
	borders_y = (HEIGHT / 2) - HEIGHT / 30;
	i = 0;
	while (i < var->rows)
	{
		j = 0;
		while (j < var->cols)
		{
			while (fabs((float)map[i][j].x * var->scale) >= borders_x)
				var->scale -= 0.0005;
			while (fabs((float)map[i][j].y * var->scale) >= borders_y)
				var->scale -= 0.0005;
			j++;
		}
		i++;
	}
}

t_height	min_max_height(t_point **map, t_var *var)
{
	t_height	height;
	int			i;
	int			j;

	height.min = INT_MAX;
	height.max = INT_MIN;
	i = 0;
	while (i < var->rows)
	{
		j = 0;
		while (j < var->cols)
		{
			if (map[i][j].z > height.max)
				height.max = map[i][j].z;
			if (map[i][j].z < height.min)
				height.min = map[i][j].z;
			j++;
		}
		i++;
	}
	return (height);
}

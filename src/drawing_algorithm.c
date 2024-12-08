/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 03:32:43 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	calculate_color(int height, int min_h, int max_h)
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

void	drawline_v(t_point *point1, t_point *point2, t_modifiers map_2d, t_data *img)
{
	int	numerator;
	int	x;
	int	y;
	int	z;
	int	i;

	numerator = map_2d.w / 2;
	i = 0;
	x = point1->x;
	y = point1->y;
	z = point1->z;
	while (i++ <= map_2d.w)
	{
		if (map_2d.w)
			z = point1->z - point1->z * (i / (float)map_2d.w)
				+ point2->z * (i / (float)map_2d.w);
		if (z < map_2d.height.min)
			z = map_2d.height.min;
		my_mlx_pixel_put(img, x, y,
			calculate_color(z, map_2d.height.min, map_2d.height.max));
		numerator += map_2d.h;
		y += map_2d.dy;
		if (numerator >= map_2d.w)
		{
			numerator -= map_2d.w;
			x += map_2d.dx;
		}
	}
}

void	drawline_h(t_point *point1, t_point *point2, t_modifiers map_2d, t_data *img)
{
	int	numerator;
	int	x;
	int	y;
	int	z;
	int	i;

	numerator = map_2d.w / 2;
	x = point1->x;
	y = point1->y;
	z = point1->z;
	i = 0;
	while (i++ <= map_2d.w)
	{
		if (map_2d.w)
			z = point1->z - point1->z * (i / (float)map_2d.w)
				+ point2->z * (i / (float)map_2d.w);
		if (z < map_2d.height.min)
			z = map_2d.height.min;
		my_mlx_pixel_put(img, point1->x, point1->y,
			calculate_color(z, map_2d.height.min, map_2d.height.max));
		numerator += map_2d.h;
		x += map_2d.dx;
		if (numerator >= map_2d.w)
		{
			numerator -= map_2d.w;
			y += map_2d.dy;
		}
	}
}

int	absolut(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

void	drawline(t_point *point1, t_point *point2, t_height height, t_data *img)
{
	t_modifiers	map;

	map.dx = 0;
	map.dy = 0;
	map.height = height;
	if (point2->x - point1->x < 0)
		map.dx = -1;
	else if (point2->x - point1->x > 0)
		map.dx = 1;
	if (point2->y - point1->y < 0)
		map.dy = -1;
	else if (point2->y - point1->y > 0)
		map.dy = 1;
	if (absolut(point2->x - point1->x) > absolut(point2->y - point1->y))
	{
		map.w = absolut(point2->x - point1->x);
		map.h = absolut(point2->y - point1->y);
		drawline_h(point1, point2, map, img);
	}
	else
	{
		map.w = absolut(point2->y - point1->y);
		map.h = absolut(point2->x - point1->x);
		drawline_v(point1, point2, map, img);
	}
}

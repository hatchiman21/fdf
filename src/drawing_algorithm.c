/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/06 15:41:50 by aatieh           ###   ########.fr       */
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

void	drawline_v(t_line *res, t_height height, t_modifiers m, t_data *img)
{
	int	numerator;
	int	z;
	int	i;

	numerator = m.w / 2;
	i = 0;
	z = res->z0;
	while (i++ <= m.w)
	{
		if (m.w)
			z = res->z0 - res->z0 * (i / (float)m.w)
				+ res->z1 * (i / (float)m.w);
		if (z < height.min)
			z = height.min;
		my_mlx_pixel_put(img, res->x0, res->y0,
			calculate_color(z, height.min, height.max));
		numerator += m.h;
		res->y0 += m.dy;
		if (numerator >= m.w)
		{
			numerator -= m.w;
			res->x0 += m.dx;
		}
	}
}

void	drawline_h(t_line *res, t_height height, t_modifiers m, t_data *img)
{
	int	numerator;
	int	z;
	int	i;

	numerator = m.w / 2;
	z = res->z0;
	i = 0;
	while (i++ <= m.w)
	{
		if (m.w)
			z = res->z0 - res->z0 * (i / (float)m.w)
				+ res->z1 * (i / (float)m.w);
		if (z < height.min)
			z = height.min;
		my_mlx_pixel_put(img, res->x0, res->y0,
			calculate_color(z, height.min, height.max));
		numerator += m.h;
		res->x0 += m.dx;
		if (numerator >= m.w)
		{
			numerator -= m.w;
			res->y0 += m.dy;
		}
	}
}

int	absolut(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

void	drawline(t_line *res, t_height height, t_data *img)
{
	t_modifiers	modifiers;

	modifiers.dx = 0;
	modifiers.dy = 0;
	if (res->x1 - res->x0 < 0)
		modifiers.dx = -1;
	else if (res->x1 - res->x0 > 0)
		modifiers.dx = 1;
	if (res->y1 - res->y0 < 0)
		modifiers.dy = -1;
	else if (res->y1 - res->y0 > 0)
		modifiers.dy = 1;
	if (absolut(res->x1 - res->x0) > absolut(res->y1 - res->y0))
	{
		modifiers.w = absolut(res->x1 - res->x0);
		modifiers.h = absolut(res->y1 - res->y0);
		drawline_h(res, height, modifiers, img);
	}
	else
	{
		modifiers.w = absolut(res->y1 - res->y0);
		modifiers.h = absolut(res->x1 - res->x0);
		drawline_v(res, height, modifiers, img);
	}
}

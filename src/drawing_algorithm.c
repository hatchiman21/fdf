/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/09 21:34:04 by aatieh           ###   ########.fr       */
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
		put_pixel_to_image(img, res->x0, res->y0,
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
		put_pixel_to_image(img, res->x0, res->y0,
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
	if (fabs(res->x1 - res->x0) > fabs(res->y1 - res->y0))
	{
		modifiers.w = fabs(res->x1 - res->x0);
		modifiers.h = fabs(res->y1 - res->y0);
		drawline_h(res, height, modifiers, img);
	}
	else
	{
		modifiers.w = fabs(res->y1 - res->y0);
		modifiers.h = fabs(res->x1 - res->x0);
		drawline_v(res, height, modifiers, img);
	}
}

void	draw(t_var *var)
{
	t_height	height;
	float		scale;
	t_line		*line;

	line = var->d2_line;
	scale = get_scale(line, var);
	apply_zoom_to_lines(line, scale);
	height = min_max_height(line);
	while (line)
	{
		drawline(line, height, &var->img);
		line = line->next;
	}
}

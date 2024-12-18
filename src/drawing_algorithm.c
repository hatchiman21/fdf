/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/18 15:28:59 by aatieh           ###   ########.fr       */
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

void	drawline_v(t_line *res, t_var *var, t_modifiers m)
{
	int	z;
	int	i;
	int	x;
	int	y;

	i = 0;
	z = res->z0;
	x = (res->x0 * var->scale + var->offset_x);
	y = (res->y0 * var->scale + var->offset_y);
	while (i++ <= m.w)
	{
		if (m.w)
			z = res->z0 - res->z0 * (i / (float)m.w)
				+ res->z1 * (i / (float)m.w);
		put_pixel_to_image(&var->img, x, y,
			calculate_color(z, var->height.min, var->height.max));
		m.numerator += m.h;
		y += m.dy;
		if (m.numerator >= m.w)
		{
			m.numerator -= m.w;
			x += m.dx;
		}
	}
}

void	drawline_h(t_line *res, t_var *var, t_modifiers m)
{
	int	z;
	int	i;
	int	x;
	int	y;

	z = res->z0;
	i = 0;
	x = (res->x0 * var->scale + var->offset_x);
	y = (res->y0 * var->scale + var->offset_y);
	while (i++ <= m.w)
	{
		if (m.w)
			z = res->z0 - res->z0 * (i / (float)m.w)
				+ res->z1 * (i / (float)m.w);
		put_pixel_to_image(&var->img, x, y,
			calculate_color(z, var->height.min, var->height.max));
		m.numerator += m.h;
		x += m.dx;
		if (m.numerator >= m.w)
		{
			m.numerator -= m.w;
			y += m.dy;
		}
	}
}

void	drawline(t_line *res, t_var *var, t_modifiers *modifiers)
{
	if (res->x1 - res->x0 < 0)
		modifiers->dx = -1;
	else if (res->x1 - res->x0 > 0)
		modifiers->dx = 1;
	if (res->y1 - res->y0 < 0)
		modifiers->dy = -1;
	else if (res->y1 - res->y0 > 0)
		modifiers->dy = 1;
	if (fabs((float)res->x1 - res->x0) > fabs((float)res->y1 - res->y0))
	{
		modifiers->w = fabs((float)res->x1 - res->x0) * var->scale;
		modifiers->h = fabs((float)res->y1 - res->y0) * var->scale;
		modifiers->numerator = modifiers->w / 2;
		drawline_h(res, var, *modifiers);
	}
	else
	{
		modifiers->w = fabs((float)res->y1 - res->y0) * var->scale;
		modifiers->h = fabs((float)res->x1 - res->x0) * var->scale;
		modifiers->numerator = modifiers->w / 2;
		drawline_v(res, var, *modifiers);
	}
}

void	draw(t_line *line, t_var *var)
{
	t_modifiers	modifiers;
	int			x0;
	int			y0;
	int			x1;
	int			y1;

	var->height = min_max_height(line);
	while (line)
	{
		modifiers.dx = 0;
		modifiers.dy = 0;
		x0 = line->x0 * var->scale + var->offset_x;
		y0 = line->y0 * var->scale + var->offset_y;
		x1 = line->x1 * var->scale + var->offset_x;
		y1 = line->y1 * var->scale + var->offset_y;
		if ((x0 < 0 && x1 < 0) || (x0 > WIDTH && x1 > WIDTH)
			|| (y0 < 0 && y1 < 0) || (y0 > HEIGHT && y1 > HEIGHT))
		{
			line = line->next;
			continue ;
		}
		drawline(line, var, &modifiers);
		line = line->next;
	}
}

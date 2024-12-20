/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/20 15:05:23 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	drawline_v(t_line *res, t_var *var, t_modifiers m)
{
	int	z;
	int	i;

	i = 0;
	z = res->z0;
	while (i++ <= m.w)
	{
		if (m.w)
			z = res->z0 - res->z0 * (i / (float)m.w)
				+ res->z1 * (i / (float)m.w);
		put_pixel_to_image(&var->img, res->x0, res->y0,
			get_color(z, var->height.min, var->height.max));
		m.numerator += m.h;
		res->y0 += m.dy;
		if (m.numerator >= m.w)
		{
			m.numerator -= m.w;
			res->x0 += m.dx;
		}
	}
}

void	drawline_h(t_line *res, t_var *var, t_modifiers m)
{
	int	z;
	int	i;

	z = res->z0;
	i = 0;
	while (i++ <= m.w)
	{
		if (m.w)
			z = res->z0 - res->z0 * (i / (float)m.w)
				+ res->z1 * (i / (float)m.w);
		put_pixel_to_image(&var->img, res->x0, res->y0,
			get_color(z, var->height.min, var->height.max));
		m.numerator += m.h;
		res->x0 += m.dx;
		if (m.numerator >= m.w)
		{
			m.numerator -= m.w;
			res->y0 += m.dy;
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
		modifiers->w = fabs((float)res->x1 - res->x0);
		modifiers->h = fabs((float)res->y1 - res->y0);
		modifiers->numerator = modifiers->w / 2;
		drawline_h(res, var, *modifiers);
	}
	else
	{
		modifiers->w = fabs((float)res->y1 - res->y0);
		modifiers->h = fabs((float)res->x1 - res->x0);
		modifiers->numerator = modifiers->w / 2;
		drawline_v(res, var, *modifiers);
	}
}

void	draw_connected_lines(t_var *var, int i, int j)
{
	t_modifiers	modifiers;
	t_line		line;

	modifiers.dx = 0;
	modifiers.dy = 0;
	if (j + 1 < var->cols)
	{
		line = calculate_line_coordinates(i, j, var, 1);
		if (line_in_screen(&line))
			drawline(&line, var, &modifiers);
	}
	if (i + 1 < var->rows)
	{
		line = calculate_line_coordinates(i, j, var, 0);
		if (line_in_screen(&line))
			drawline(&line, var, &modifiers);
	}
}

void	draw(t_var *var)
{
	int			i;
	int			j;

	var->height = min_max_height(var->grid_2d, var);
	i = 0;
	while (i < var->rows)
	{
		j = 0;
		while (j < var->cols)
		{
			draw_connected_lines(var, i, j);
			j++;
		}
		i++;
	}
}

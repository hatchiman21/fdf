/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:49:44 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/20 14:50:39 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	place_image(t_var *var, t_var *tmp, int start_draw, int start_rotare)
{
	var->img.img = mlx_new_image(var->mlx_win->mlx, WIDTH, HEIGHT);
	if (!var->img.img)
	{
		ft_dprintf(2, "Malloc for img failed\n");
		free_all(tmp);
	}
	if (!var->img.addr)
	{
		var->img.addr = mlx_get_data_addr(var->img.img,
				&var->img.bits_per_pixel,
				&var->img.line_length, &var->img.endian);
		if (!var->img.addr)
		{
			ft_dprintf(2, "Malloc for img address failed\n");
			free_all(tmp);
		}
	}
	if (start_draw)
	{
		if (start_rotare)
			apply_rotation(var);
		draw(var);
		mlx_put_image_to_window(var->mlx_win->mlx,
			var->mlx_win->win, var->img.img, 0, 0);
	}
}

int	mouse_zoom(int button, int x, int y, t_var *var)
{
	float	scale_in;
	t_var	*tmp;

	tmp = var;
	if (!var->on_display)
		var = var->second;
	if (button == 4 || button == 5)
	{
		scale_in = var->scale;
		x = (x - var->offset_x) / scale_in;
		y = (y - var->offset_y) / scale_in;
		if (button == 4)
			var->scale *= 1.1;
		else
			var->scale *= 0.9;
		var->offset_x = (x * scale_in + var->offset_x) - x * var->scale;
		var->offset_y = (y * scale_in + var->offset_y) - y * var->scale;
		mlx_destroy_image(var->mlx_win->mlx, var->img.img);
		place_image(var, tmp, 1, 1);
	}
	return (0);
}

void	assigne_point(t_point *point, t_var *var, int i, int j)
{
	int		x;
	int		y;
	int		z;

	x = point->x;
	y = point->y;
	z = point->z;
	if (var->projection == ISOMETRIC)
	{
		var->grid_2d[i][j].x = x - y;
		var->grid_2d[i][j].y = ((x + y) / 2) - z;
	}
	else
	{
		var->grid_2d[i][j].x = x;
		var->grid_2d[i][j].y = y;
	}
	var->grid_2d[i][j].z = var->grid_3d[i][j];
}

void	rotate_all(t_point *point, t_var *var)
{
	int	tmp_x;
	int	tmp_y;

	tmp_y = point->y;
	point->y = tmp_y * cos(var->x_angle) + point->z * sin(var->x_angle);
	point->z = -tmp_y * sin(var->x_angle) + point->z * cos(var->x_angle);
	tmp_x = point->x;
	point->x = tmp_x * cos(var->y_angle) + point->z * sin(var->y_angle);
	point->z = -tmp_x * sin(var->y_angle) + point->z * cos(var->y_angle);
	tmp_x = point->x;
	point->x = tmp_x * cos(var->z_angle) - point->y * sin(var->z_angle);
	point->y = tmp_x * sin(var->z_angle) + point->y * cos(var->z_angle);
}

void	apply_rotation(t_var *var)
{
	t_point	point;
	int		i;
	int		j;

	i = 0;
	while (i < var->rows)
	{
		j = 0;
		while (j < var->cols)
		{
			point.x = i * 200;
			point.y = j * 200;
			point.z = var->grid_3d[i][j] * 200;
			rotate_all(&point, var);
			assigne_point(&point, var, i, j);
			j++;
		}
		i++;
	}
}

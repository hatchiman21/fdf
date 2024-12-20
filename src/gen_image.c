/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:34:10 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/20 15:04:58 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	offset_before_scaling(t_point **map, t_var *var)
{
	int			i;
	int			j;
	t_height	x_h;
	t_height	y_h;

	i = 0;
	get_bounds(map, &x_h, &y_h, var);
	while (i < var->rows)
	{
		j = 0;
		while (j < var->cols)
		{
			map[i][j].x -= (x_h.max + x_h.min) / 2;
			map[i][j].y -= (y_h.max + y_h.min) / 2;
			j++;
		}
		i++;
	}
}

t_line	calculate_line_coordinates(int i, int j, t_var *var, int vertical)
{
	t_line	line;

	line.x0 = var->grid_2d[i][j].x * var->scale + var->offset_x;
	line.y0 = var->grid_2d[i][j].y * var->scale + var->offset_y;
	line.z0 = var->grid_2d[i][j].z;
	if (vertical)
	{
		line.x1 = var->grid_2d[i][j + 1].x * var->scale + var->offset_x;
		line.y1 = var->grid_2d[i][j + 1].y * var->scale + var->offset_y;
		line.z1 = var->grid_2d[i][j + 1].z;
	}
	else
	{
		line.x1 = var->grid_2d[i + 1][j].x * var->scale + var->offset_x;
		line.y1 = var->grid_2d[i + 1][j].y * var->scale + var->offset_y;
		line.z1 = var->grid_2d[i + 1][j].z;
	}
	return (line);
}

int	line_in_screen(t_line *line)
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;

	x0 = line->x0;
	x1 = line->x1;
	y0 = line->y0;
	y1 = line->y1;
	if ((x0 < 0 && x1 < 0) || (x0 > WIDTH && x1 > WIDTH)
		|| (y0 < 0 && y1 < 0) || (y0 > HEIGHT && y1 > HEIGHT))
		return (0);
	return (1);
}

t_point	**assign_2d_grid(int rows, int cols)
{
	t_point	**map;
	int		i;

	if (rows == 0 || cols == 0)
	{
		ft_dprintf(2, "Invalid map\n");
		return (NULL);
	}
	map = malloc(rows * sizeof(t_point *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		map[i] = malloc(cols * sizeof(t_point));
		if (!map[i])
		{
			free_2d_grid(map, i);
			return (NULL);
		}
		i++;
	}
	return (map);
}

void	initialize_and_draw(t_var *var, int second)
{
	int	x;
	int	y;

	offset_before_scaling(var->grid_2d, var);
	get_scale(var->grid_2d, var);
	x = var->grid_2d[0][0].x;
	y = var->grid_2d[0][0].y;
	apply_rotation(var);
	var->offset_x = (x * var->scale + WIDTH / 2) - var->scale;
	var->offset_y = (y * var->scale + HEIGHT / 2) - var->scale;
	if (!second)
	{
		draw(var);
		mlx_hook(var->mlx_win->win, 2, 1L << 0, handle_keys, var);
		mlx_hook(var->mlx_win->win, 17, 0, free_all, var);
		mlx_mouse_hook(var->mlx_win->win, mouse_zoom, var);
		mlx_put_image_to_window(var->mlx_win->mlx,
			var->mlx_win->win, var->img.img, 0, 0);
		mlx_loop(var->mlx_win->mlx);
	}
}

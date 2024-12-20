/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:37:00 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/20 15:02:42 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	initialize_mlx(t_var *var, int second)
{
	t_var	*tmp;

	tmp = var;
	if (!second)
	{
		var->mlx_win->mlx = mlx_init();
		if (!var->mlx_win->mlx)
		{
			ft_dprintf(2, "mlx init malloc failed\n");
			free_all(tmp);
		}
		var->mlx_win->win = mlx_new_window(var->mlx_win->mlx,
				WIDTH, HEIGHT, "window");
		if (!var->mlx_win->win)
		{
			ft_dprintf(2, "mlx window malloc failed\n");
			free_all(tmp);
		}
	}
	else
		var = var->second;
	var->mlx_win = tmp->mlx_win;
	var->img.addr = NULL;
	place_image(var, tmp, 0, 0);
}

void	make_second_var(t_var *var)
{
	var->second = malloc(sizeof(t_var));
	if (!var->second)
	{
		ft_dprintf(2, "Malloc for second var failed\n");
		free_all(var);
	}
	initialize_var(var->second, PARALLEL);
	var->second->grid_3d = var->grid_3d;
	var->second->rows = var->rows;
	var->second->cols = var->cols;
	var->second->grid_2d = assign_2d_grid(var->rows, var->cols);
	if (!var->second->grid_2d)
	{
		ft_dprintf(2, "Malloc for second grid failed\n");
		free_all(var);
	}
	apply_rotation(var->second);
	initialize_mlx(var, 1);
	initialize_and_draw(var->second, 1);
}

void	change_to_second(t_var *var)
{
	mlx_destroy_image(var->mlx_win->mlx, var->img.img);
	if (!var->second)
		make_second_var(var);
	else
	{
		var->second->img.img = mlx_new_image(var->mlx_win->mlx, WIDTH, HEIGHT);
		if (!var->second->img.img)
		{
			ft_dprintf(2, "Malloc for second img failed\n");
			free_all(var);
		}
	}
	draw(var->second);
	mlx_put_image_to_window(var->mlx_win->mlx,
		var->mlx_win->win, var->second->img.img, 0, 0);
	var->on_display = 0;
}

void	move_drawing(int keycode, t_var *var, t_var *tmp)
{
	if (keycode == UP)
		var->offset_y -= HEIGHT / 50;
	if (keycode == LEFT)
		var->offset_x -= WIDTH / 50;
	if (keycode == DOWN)
		var->offset_y += HEIGHT / 50;
	if (keycode == RIGHT)
		var->offset_x += WIDTH / 50;
	if (keycode == X)
		var->x_angle += 2 * (PI / 180);
	if (keycode == Y)
		var->y_angle += 2 * (PI / 180);
	if (keycode == Z)
		var->z_angle += 2 * (PI / 180);
	mlx_destroy_image(var->mlx_win->mlx, var->img.img);
	place_image(var, tmp, 1, 1);
}

int	handle_keys(int keycode, t_var *var)
{
	t_var	*tmp;

	tmp = var;
	if (keycode == 50 && var->on_display)
		change_to_second(var);
	if (keycode == ESC)
		free_all(var);
	if (keycode == 49 && var->on_display == 0)
	{
		mlx_destroy_image(var->mlx_win->mlx, var->second->img.img);
		place_image(var, tmp, 1, 0);
		var->on_display = 1;
		var->second->on_display = 0;
	}
	if (var->on_display == 0 && var->second)
		var = var->second;
	if ((keycode <= DOWN && keycode >= LEFT) || (keycode >= X && keycode <= Z))
		move_drawing(keycode, var, tmp);
	return (0);
}

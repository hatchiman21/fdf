/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:37:00 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/18 15:44:33 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + y * data->line_length + (x * data->bits_per_pixel) / 8;
	*(unsigned int *)dst = color;
}

int	initialize_mlx(t_var *var)
{
	var->mlx = mlx_init();
	if (!var->mlx)
	{
		ft_dprintf(2, "mlx init malloc failed\n");
		free_all(var);
		return (4);
	}
	var->win = mlx_new_window(var->mlx, WIDTH, HEIGHT, "window");
	var->img.img = mlx_new_image(var->mlx, WIDTH, HEIGHT);
	if (!var->win || !var->img.img)
	{
		ft_dprintf(2, "mlx components malloc failed\n");
		free_all(var);
		return (5);
	}
	var->img.addr = mlx_get_data_addr(var->img.img,
			&var->img.bits_per_pixel, &var->img.line_length, &var->img.endian);
	if (!var->img.addr)
	{
		ft_dprintf(2, "mlx address malloc failed\n");
		free_all(var);
		return (6);
	}
	return (0);
}

int	mouse_zoom(int button, int x, int y, t_var *var)
{
	float	scale_in;

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
		mlx_destroy_image(var->mlx, var->img.img);
		var->img.img = mlx_new_image(var->mlx, WIDTH, HEIGHT);
		var->img.addr = mlx_get_data_addr(var->img.img,
				&var->img.bits_per_pixel, &var->img.line_length,
				&var->img.endian);
		draw(var->d2_line, var);
		mlx_put_image_to_window(var->mlx, var->win, var->img.img, 0, 0);
	}
	return (0);
}

int	handle_keys(int keycode, t_var *var)
{
	if (keycode == ESC)
		close_exit(var);
	if (keycode >= LEFT && keycode <= DOWN)
	{
		if (keycode == LEFT)
			var->offset_x -= WIDTH / 50;
		if (keycode == RIGHT)
			var->offset_x += WIDTH / 50;
		if (keycode == UP)
			var->offset_y -= HEIGHT / 50;
		if (keycode == DOWN)
			var->offset_y += HEIGHT / 50;
		mlx_destroy_image(var->mlx, var->img.img);
		var->img.img = mlx_new_image(var->mlx, WIDTH, HEIGHT);
		var->img.addr = mlx_get_data_addr(var->img.img,
				&var->img.bits_per_pixel, &var->img.line_length,
				&var->img.endian);
		draw(var->d2_line, var);
		mlx_put_image_to_window(var->mlx, var->win, var->img.img, 0, 0);
	}
	return (0);
}

void	initialize_and_draw(t_var *var)
{
	t_line	*line;

	var->mlx = NULL;
	var->win = NULL;
	var->img.img = NULL;
	if (initialize_mlx(var))
		return ;
	line = var->d2_line;
	offset_before_scaling(line);
	var->scale = get_scale(line);
	var->offset_x = WIDTH / 2;
	var->offset_y = HEIGHT / 2;
	draw(line, var);
	mlx_hook(var->win, 2, 1L << 0, handle_keys, var);
	mlx_hook(var->win, 17, 0, close_exit, var);
	mlx_mouse_hook(var->win, mouse_zoom, var);
	mlx_put_image_to_window(var->mlx, var->win, var->img.img, 0, 0);
	mlx_loop(var->mlx);
}

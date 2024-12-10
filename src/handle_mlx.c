/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:37:00 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/10 19:25:05 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	char	*dst;

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

void	initialize_and_draw(t_var *var)
{
	var->mlx = NULL;
	var->win = NULL;
	var->img.img = NULL;
	if (initialize_mlx(var))
		return ;
	draw(var);
	mlx_put_image_to_window(var->mlx, var->win, var->img.img, 20, 20);
	mlx_hook(var->win, 2, 1L << 0, close_win, var);
	mlx_hook(var->win, 17, 0, close_exit, var);
	mlx_loop(var->mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/03 21:37:46 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + y * data->line_length + (x * data->bits_per_pixel) / 8;
	*(unsigned int *)dst = color;
}

void	apply_scale(t_line *lst, float scale)
{
	while (lst)
	{
		lst->x0 = (int)round(scale * lst->x0);
		lst->y0 = (int)round(scale * lst->y0);
		lst->x1 = (int)round(scale * lst->x1);
		lst->y1 = (int)round(scale * lst->y1);
		lst->z0 = (int)round(scale * lst->z0);
		lst->z1 = (int)round(scale * lst->z1);
		lst = lst->next;
	}
}

void	draw(char ***cor, t_line *res, t_data *img)
{
	t_height	height;
	float scale;
	int	y;
	int	x;

	scale = get_scale(res);
	apply_scale(res, scale);
	height = min_max_height(res);
	x = 0;
	y = 0;
	printf("scale is %f max height :%d min height %d\n", scale * 100, height.max, height.min);
	while (res)
	{
		drawline(res, height, img);
		res = res->next;
	}
	ft_printf("max y is %d and max x is %d\n", y, x);
}

void	first(char ***cor, t_var *var)
{
	var->lines_head = plot(cor, &(var->img));
	if (!var->lines_head)
	{
		ft_dprintf(2, "Malloc failed\n");
		exit(3);
	}
	shift(var->lines_head);
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, 920, 920, "window");
	var->img.img = mlx_new_image(var->mlx, 920, 920);
	var->img.addr = mlx_get_data_addr(var->img.img,
			&var->img.bits_per_pixel, &var->img.line_length, &var->img.endian);
	draw(cor, var->lines_head, &(var->img));
	mlx_put_image_to_window(var->mlx, var->win, var->img.img, 20, 20);
	mlx_hook(var->win, 2, 1L << 0, close_win, var);
	mlx_hook(var->win, 17, 0, close_exit, var);
	mlx_loop(var->mlx);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_var	var;

	if (argc != 2)
	{
		ft_dprintf(2, "Wrong number of inputs\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "Error opening %s\n", argv[1]);
		return (2);
	}
	var.cor = grap_input(argv[1], fd);
	if (!var.cor)
	{
		ft_dprintf(2, "Malloc failed\n");
		return (3);
	}
	close(fd);
	first(var.cor, &var);
	return (0);
}

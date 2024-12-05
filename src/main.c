/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/04 18:38:01 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	highest_in_cor(char ***cor)
{
	int	i;
	int	j;
	int	highest;

	i = 0;
	highest = 0;
	while (cor[i])
	{
		j = 0;
		while (cor[i][j])
		{
			if (ft_atoi(cor[i][j]) > highest)
				highest = ft_atoi(cor[i][j]);
			j++;
		}
		i++;
	}
	return (highest);
}

void	print_cor(char ***cor)
{
	int	i;
	int	j;

	i = 0;
	while (cor[i])
	{
		j = 0;
		while (cor[i][j])
		{
			ft_printf("%s ", cor[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_res(t_line *res)
{
	while (res)
	{
		ft_printf("x0: %d y0: %d z0: %d x1: %d y1: %d z1: %d\n",
			res->x0, res->y0, res->z0, res->x1, res->y1, res->z1);
		res = res->next;
	}
}

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
		lst = lst->next;
	}
}

void	draw(char ***cor, t_line *res, t_data *img)
{
	t_height	height;
	float		scale;

	scale = get_scale(res);
	apply_scale(res, scale);
	height = min_max_height(res);
	while (res)
	{
		drawline(res, height, img);
		res = res->next;
	}
}

void	first(char ***cor, t_var *var)
{
	var->mlx = mlx_init();
	if (!var->mlx)
	{
		ft_dprintf(2, "mlx init malloc failed\n");
		free_all(var, cor);
		exit(4);
	}
	var->win = mlx_new_window(var->mlx, 920, 920, "window");
	var->img.img = mlx_new_image(var->mlx, 920, 920);
	if (!var->win || !var->img.img)
	{
		ft_dprintf(2, "mlx components malloc failed\n");
		free_all(var, cor);
		exit(5);
	}
	var->img.addr = mlx_get_data_addr(var->img.img,
			&var->img.bits_per_pixel, &var->img.line_length, &var->img.endian);
	if (!var->img.addr)
	{
		ft_dprintf(2, "mlx address malloc failed\n");
		free_all(var, cor);
		exit(6);
	}
	draw(cor, var->res, &(var->img));
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
		return (ft_dprintf(2, "Wrong number of inputs\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(2, "Error opening %s\n", argv[1]), 2);
	var.cor = grap_input(argv[1], fd);
	close(fd);
	if (!var.cor)
		return (ft_dprintf(2, "Malloc failed\n"), 3);
	var.res = plot(var.cor, &(var.img));
	if (!var.res)
	{
		ft_dprintf(2, "Malloc failed\n");
		free_cor(var.cor);
		exit(3);
	}
	shift(var.res);
	first(var.cor, &var);
	return (0);
}

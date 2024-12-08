/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 03:31:30 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	highest_in_map(char ***map)
{
	int	i;
	int	j;
	int	highest;

	i = 0;
	highest = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_atoi(map[i][j]) > highest)
				highest = ft_atoi(map[i][j]);
			j++;
		}
		i++;
	}
	return (highest);
}

void	print_map(char ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ft_printf("%s ", map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

// void	print_res(t_line *res)
// {
// 	while (res)
// 	{
// 		ft_printf("x0: %d y0: %d z0: %d x1: %d y1: %d z1: %d\n",
// 			res->x0, res->y0, res->z0, res->x1, res->y1, res->z1);
// 		res = res->next;
// 	}
// }

void print_points(t_point *point)
{
	t_point *row_start;
	t_point *current;

	row_start = point;
	while (row_start)
	{
		current = row_start;
		while (current)
		{
			printf("Point: (%d, %d)\n", current->x, current->y);
			current = current->next_x;
		}
		row_start = row_start->next_y;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + y * data->line_length + (x * data->bits_per_pixel) / 8;
	*(unsigned int *)dst = color;
}

void	zoom(t_point *point, float scale)
{
	t_point	*tmp;
	t_point	*tmp2;

	tmp = point->next_y;
	while (point)
	{
		tmp2 = point->next_x;
		point->x *= scale;
		point->y *= scale;
		if (tmp2)
			point = tmp2;
		else
		{
			point = tmp;
			if (tmp)
				tmp = tmp->next_y;
		}
	}
}

void	draw(t_var *var, t_point *point)
{
	t_height	height;
	t_point		*next_row;
	t_point		*tmp2;
	float		scale;

	scale = get_scale(point, var);
	// print_points(var->point);
	zoom(point, scale);
	height = min_max_height(point);
	next_row = point->next_y;
	while (point)
	{
		tmp2 = point->next_x;
		if (point->next_y)
			drawline(point, point->next_y, height, &var->img);
		if (point->next_x)
			drawline(point, point->next_x, height, &var->img);
		if (point->next_x)
			point = point->next_x;
		else
		{
			point = next_row;
			if (next_row)
				next_row = next_row->next_y;
		}
	}
}

void	first(t_var *var)
{
	var->mlx = mlx_init();
	if (!var->mlx)
	{
		ft_dprintf(2, "mlx init malloc failed\n");
		free_all(var, var->map);
		exit(4);
	}
	var->win = mlx_new_window(var->mlx, var->width, var->height, "window");
	var->img.img = mlx_new_image(var->mlx, var->width, var->height);
	if (!var->win || !var->img.img)
	{
		ft_dprintf(2, "mlx components malloc failed\n");
		free_all(var, var->map);
		exit(5);
	}
	var->img.addr = mlx_get_data_addr(var->img.img,
			&var->img.bits_per_pixel, &var->img.line_length, &var->img.endian);
	if (!var->img.addr)
	{
		ft_dprintf(2, "mlx address malloc failed\n");
		free_all(var, var->map);
		exit(6);
	}
	// print_points(var->point);
	draw(var, var->point);
	mlx_put_image_to_window(var->mlx, var->win, var->img.img, 0, 0);
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
	var.map = grap_map(argv[1], fd);
	close(fd);
	if (!var.map)
		return (ft_dprintf(2, "Malloc failed\n"), 3);
	var.point = gen_2d_map(var.map, &(var.img));
	var.width = 1600;
	var.height = 920;
	if (!var.point)
	{
		ft_dprintf(2, "Malloc failed\n");
		free_map(var.map);
		exit(3);
	}
	offset_map(var.point, &var);
	first(&var);
	return (0);
}

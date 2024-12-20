/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/20 15:03:07 by aatieh           ###   ########.fr       */
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

void	intialize_angles(t_var *var, int projection)
{
	if (projection == ISOMETRIC)
	{
		var->x_angle = 66 * (PI / 180);
		var->y_angle = 37 * (PI / 180);
		var->z_angle = 155 * (PI / 180);
	}
	else
	{
		var->x_angle = 180 * (PI / 180);
		var->y_angle = 0 * (PI / 180);
		var->z_angle = 90 * (PI / 180);
	}
	var->offset_x = WIDTH / 2;
	var->offset_y = HEIGHT / 2;
	var->projection = projection;
	var->cols = 0;
	var->rows = 0;
}

void	initialize_var(t_var *var, int projection)
{
	var->mlx_win = NULL;
	var->img.img = NULL;
	var->on_display = 1;
	var->second = NULL;
	var->grid_3d = NULL;
	var->grid_2d = NULL;
	intialize_angles(var, projection);
	if (projection == ISOMETRIC)
	{
		var->mlx_win = malloc(sizeof(t_mlx));
		if (var->mlx_win)
		{
			var->mlx_win->mlx = NULL;
			var->mlx_win->win = NULL;
		}
		else
		{
			ft_dprintf(2, "Malloc failed for mlx_win\n");
			free_all(var);
		}
	}
}

int	initialize_grids(t_var *var, char *filename)
{
	if (grap_file(filename, var) == -1 || !var->cor)
	{
		ft_dprintf(2, "Malloc failed while reading the file\n");
		free_all(var);
	}
	grap_3d_map(var);
	free_cor(var->cor);
	if (!var->grid_3d)
	{
		free_all(var);
		return (ft_dprintf(2, "3d_grid Malloc failed\n"), 3);
	}
	var->grid_2d = assign_2d_grid(var->rows, var->cols);
	if (!var->grid_2d)
	{
		ft_dprintf(2, "2d_grid Malloc failed\n");
		free_all(var);
	}
	apply_rotation(var);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_var	var;
	int		fd;

	if (argc != 2)
	{
		if (argc < 2)
			ft_dprintf(2, "missing input\n");
		else
			ft_dprintf(2, "too many inputs\n");
		exit (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit (2);
	}
	close(fd);
	initialize_var(&var, ISOMETRIC);
	initialize_grids(&var, argv[1]);
	initialize_mlx(&var, 0);
	initialize_and_draw(&var, 0);
	return (0);
}

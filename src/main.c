/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/28 21:58:06 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	***free_cor(char ***string)
{
	int	i;
	int	j;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i])
	{
		j = 0;
		while (string[i][j])
			free(string[i][j++]);
		free(string[i++]);
	}
	free (string);
	return (NULL);
}

int	free_lines(t_line *lines)
{
	t_line	*tmp;

	while (lines)
	{
		tmp = lines->next;
		free(lines);
		lines = tmp;
	}
	return (0);
}

void	free_split(char **string)
{
	int	i;

	i = 0;
	if (!string)
		return ;
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
}

void	print_cor(char ***cor)
{
	int	i;
	int	j;

	if (!cor)
		return ;
	i = 0;
	while (cor[i])
	{
		j = 0;
		while (cor[i][j])
			ft_printf("%s ", cor[i][j++]);
		i++;
		ft_printf("\n");
	}
}

// void	print_res(int **res)
// {
// 	int	i;
// 	int	j;

// 	if (!res)
// 		return ;
// 	i = 0;
// 	while (res[i])
// 	{
// 		j = 0;
// 		while (res[i][j])
// 			ft_printf("%d ", res[i][j++]);
// 		i++;
// 		ft_printf("\n");
// 	}
// }

void	print_lines(t_line *lines)
{
	t_line	*tmp;

	tmp = lines;
	while (tmp)
	{
		ft_printf("Segment((%d, %d), (%d, %d))\n", tmp->x0, tmp->y0, tmp->x1, tmp->y1);
		tmp = tmp->next;
	}
}

// int	**get_res(char ***cor)
// {
// 	int	i;
// 	int	j;
// 	int	**res;

// 	i = 0;
// 	j = 0;
// 	while (cor[0][j])
// 		j++;
// 	while (cor[i])
// 		i++;
// 	res = malloc(sizeof(int *) * i);
// 	i = 0;
// 	while (cor[i])
// 	{
// 		res[i] = malloc(sizeof(int) * j);
// 		j = 0;
// 		while (cor[i][j])
// 		{
// 			res[i][j] = ft_atoi(cor[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }

char	***intial_malloc(int fd)
{
	char	***cor;
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	cor = malloc((i + 1) * sizeof(char **));
	return (cor);
}

char	***grap_input(char *arg, int fd)
{
	int		i;
	char	***cor;
	char	*line;

	cor = intial_malloc(fd);
	if (!cor)
		return (NULL);
	close(fd);
	fd = open(arg, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		cor[i] = ft_split(line, ' ');
		if (!cor[i])
			return (free_cor(cor));
		i++;
		free(line);
		line = get_next_line(fd);
	}
	cor[i] = NULL;
	return (cor);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + y * data->line_length + (x * data->bits_per_pixel) / 8;
	*(unsigned int *)dst = color;
}
/*
drawline_h if ∣dx∣>∣dy∣
*/

int	get_dest(int x_old, int y_old, int z, int is_x)
{
	// int	res;
	
	// res = 0;
	// if (is_x)
	// 	res = x - y;
	// else
	// 	res = ((x + y) / 2) - z;
	// return ((int)round(res));

	int	x_new;
	int y_new;

	x_new = x_old - y_old;
	y_new = ((x_old + y_old) / 2) - z
}


// void	line_addback(t_line **lst, t_line *new)
// {
// 	t_line	*tmp;

// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	tmp = *lst;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

// int	get_scale(int *x, int *y, int *z)
// {
	
// 	int	scale;

// 	scale = 1;
// 	while (lst)
// 	{
// 		while (scale && get_dest(x[0] * scale, y[0] * scale, z[0] * scale, 1) >= 900)
// 			scale -= 1;
// 		while (scale && get_dest(x[0] * scale, y[0] * scale, z[0] * scale, 0) >= 900)
// 			scale -= 1;
// 		while (scale && get_dest(x[1] * scale, y[1] * scale, z[1] * scale, 1) >= 900)
// 			scale -= 1;
// 		while (scale && get_dest(x[1] * scale, y[1] * scale, z[1] * scale, 0) >= 900)
// 			scale -= 1;
// 		lst = lst->next;
// 	}
// 	return (scale);
// }

float	get_scale(t_line *lst)
{
	
	float	scale;

	scale = 1;
	while (lst)
	{
		while (scale && lst->x0 * scale >= 900)
			scale -= 0.01;
		while (scale && lst->x1 * scale >= 900)
			scale -= 0.01;
		while (scale && lst->y0 * scale >= 900)
			scale -= 0.01;
		while (scale && lst->y1 * scale >= 900)
			scale -= 0.01;
		lst = lst->next;
	}
	return (scale);
}

void	compare_replace(t_line *lst, int *offset)
{
	if (lst->x0 < *offset)
		*offset = lst->x0;
	if (lst->x1 < *offset)
		*offset = lst->x1;
	if (lst->y0 < *offset)
		*offset = lst->y0;
	if (lst->y1 < *offset)
		*offset = lst->y1;
}

void	shift(t_line *res)
{
	int		offset;
	t_line	*tmp;

	offset = 0;
	tmp = res;
	while (tmp)
	{
		compare_replace(tmp, &offset);
		tmp = tmp->next;
	}
	while (res)
	{
		res->x0 -= offset;
		res->x1 -= offset;
		res->y0 -= offset;
		res->y1 -= offset;
		res = res->next;
	}
}

int	get_res(int *x, int *y, int *z, t_line **res)
{
	t_line	*node;
	t_line	*tmp;
	int		scale;

	scale = 100;
	node = malloc(sizeof(t_line));
	if (!node)
		return (free_lines(*res));
	if (!*res)
		*res = node;
	else
	{
		tmp = *res;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	node->next = NULL;
	node->x0 = get_dest(x[0] * scale, y[0] * scale, z[0] * scale, 1);
	node->y0 = get_dest(x[0] * scale, y[0] * scale, z[0] * scale, 0);
	node->x1 = get_dest(x[1] * scale, y[1] * scale, z[1] * scale, 1);
	node->y1 = get_dest(x[1] * scale, y[1] * scale, z[1] * scale, 0);
	return (1);
}

t_line	*plot(char ***cor, t_data *img)
{
	t_line	*res;
	int		y;
	int		x;

	y = 0;
	res = NULL;
	while (cor[y])
	{
		x = 0;
		while (cor[y][x])
		{
			if (cor[y + 1] && !get_res((int []){x, x}, (int []){y, (y + 1)}
				, (int []){ft_atoi(cor[y][x]), ft_atoi(cor[y + 1][x])}, &res))
				return (NULL);
			if (cor[y][x + 1] && !get_res((int []){x, (x + 1)}, (int []){y, y}
				, (int []){ft_atoi(cor[y][x]), ft_atoi(cor[y][x + 1])}, &res))
				return (NULL);
			x++;
		}
		y++;
	}
	return (res);
}

// int	tmpx;
// int	tmpy;
// int	i = 0;
// while (y <= 300)
// {
// 	x = 0;
// 	while (x <= 300)
// 	{
// 		// tmpx = get_dest(x + 10, y, 0, 1);
// 		// tmpy = get_dest(x, y + 10, 0, 0);
// 		drawline_h((int []){x, x + 10}, (int []){y, y}, img);
// 		drawline_v((int []){x, x}, (int []){y, y + 10}, img);
// 		x += 10;
// 	}
// 	i = +2;
// 	y += 10;
// }
// y = 0;
// while (y < 100)
// drawline_h((int []){0, 100}, (int []){0, 0}, img);

// while (cor[i + 1])
// {
// 	j = 0;
// 	while (cor[i][j + 1])
// 	{
// 		drawline_h((double []){0 * 4, 20 * 4}, (double []){0 * 4, 0 * 4}, img);
// 		drawline_v((double []){0 * 4, 0 * 4}, (double []){0 * 4, 20 * 4}, img);
// 		drawline_h((double []){0 * 4, 20 * 4}
//			 , (double []){20 * 4, 20 * 4}, img);
// 		drawline_v((double []){20 * 4, 20 * 4}
//			 , (double []){0 * 4, 20 * 4}, img);
// 		j++;
// 	}
// 	i++;
// }
// drawline_h((double []){0, 4 * 25}, (double []){0, 0}, img);
// drawline_v((double []){0, j * 25}, (double []){0, (i + 1) * 25}, img);

void	draw(char ***cor, t_line *res, t_data *img)
{
	// int	x;
	// int	y;
	float	scale;

	scale = get_scale(res);
	// y = 0;
	// while (cor[y])
	// {
	// 	x = 0;
	// 	while (cor[y][x])
	// 	{
	// 		// if (cor[y][x + 1])
	// 			drawline_v((int []){res->x0, res->x1},
	// 				(int []){res->y0, res->y1}, img);
	// 		// if (cor[y + 1])
	// 			drawline_v((int []){res->x0, res->x1},
	// 				(int []){res->y0, res->y1}, img);
	// 		x++;
	// 		res = res->next;
	// 	}
	// 	y++;
	// }
	printf("scale is %f\n", scale);
	while (res)
	{
		// if (ABS(res->x1 - res->x0) > ABS(res->y1 - res->y0))
		// 	drawline_v((int []){res->x0, res->x1},
		// 		(int []){res->y0, res->y1}, img);
		// else
		// 	drawline_h((int []){res->x0, res->x1},
		// 		(int []){res->y0, res->y1}, img);
		drawline_test((int []){round(res->x0 * scale), round(res->x1 * scale)},
			(int []){round(res->y0 * scale), round(res->y1 * scale)}, img);
		res = res->next;
	}
}

void	first(char ***cor)
{
	void	*mlx;
	void	*mlx_win;
	t_line	*res;
	t_data	img;

	res = plot(cor, &img);
	if (!res)
	{
		ft_dprintf(2, "Malloc failed\n");
		exit(3);
	}
	shift(res);
	print_lines(res);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 920, 920, "first test");
	img.img = mlx_new_image(mlx, 920, 920);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	draw(cor, res, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 20, 20);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, mlx_win);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	***cor;

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
	cor = grap_input(argv[1], fd);
	if (!cor)
	{
		ft_dprintf(2, "Malloc failed\n");
		return (3);
	}
	close(fd);
	first(cor);
	free_cor(cor);
	return (0);
}

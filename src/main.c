/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/03 17:24:41 by aatieh           ###   ########.fr       */
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

int	get_dest(int x, int y, int z, int is_x)
{
	int	res;
	
	res = 0;
	if (is_x)
		res = x - y;
	else
		res = ((x + y) / 2) - z;
	return ((int)round(res));
}

float	get_scale(t_line *lst)
{
	float	scale;

	scale = 1;
	while (lst)
	{
		while (scale && lst->x0 * scale >= 900)
			scale -= 0.001;
		while (scale && lst->x1 * scale >= 900)
			scale -= 0.001;
		while (scale && lst->y0 * scale >= 900)
			scale -= 0.001;
		while (scale && lst->y1 * scale >= 900)
			scale -= 0.001;
		lst = lst->next;
	}
	return (scale);
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
	node->z0 = z[0] * scale;
	node->z1 = z[1] * scale;
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

t_height	min_max_height(t_line *res)
{
	t_height	height;
	
	height.min = 0;
	height.max = 0;
	while (res)
	{
		if (res->z0 < height.min)
			height.min = res->z0;
		if (res->z1 < height.min)
			height.min = res->z1;
		if (res->z0 > height.max)
			height.max = res->z0;
		if (res->z1 > height.max)
			height.max = res->z1;
		res = res->next;
	}
	return (height);
}

void	draw(char ***cor, t_line *res, t_data *img)
{
	t_height	height;

	apply_scale(res, get_scale(res));
	height = min_max_height(res);
	while (res)
	{
		drawline(res, height,
		 img);
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
	// print_lines(res);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/22 06:06:26 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_cor(char ***string)
{
	int	i;
	int	j;

	if (!string)
		return ;
	i = 0;
	while (string[i])
	{
		j = 0;
		while (string[i][j])
			free(string[i][j++]);
		free(string[i++]);
	}
	free (string);
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
			return (free_cor(cor), NULL);
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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel) / 8);
	*(unsigned int *)dst = color;
}
/*
drawline_h if ∣dx∣>∣dy∣
*/

double	get_dest(int x, int y, int z, int is_x)
{
	double	a;
	double	res;

	if (z != 0)
		a = (2.0 * PI) / 3.0;
	else
		a = PI / 4.0;
	if (is_x)
		res = x * cos(a) + y * cos(a + 2) + z * cos(a - 2);
	else
		res = x * sin(a) + y * sin(a + 2) + z * sin(a - 2);
	return (ABS(res));
}

void	plot(char ***cor, t_data *img)
{
	t_line	dest;
	int		y;
	int		x;

	y = 0;
	// while (cor[y + 1])
	// {
	// 	x = 0;
	// 	while (cor[y][x + 1])
	// 	{
	// 		// dest.x0 = get_dest(x * 25, y * 25, ft_atoi(cor[y][x]) * 25, 1);
	// 		// dest.y0 = get_dest(x * 25, y * 25, ft_atoi(cor[y][x]) * 25, 0);
	// 		dest.x1 = get_dest(x + 1, y, ft_atoi(cor[y][x]), 1);
	// 		dest.y1 = get_dest(x + 1, y, ft_atoi(cor[y][x]), 0);
	// 		drawline_h((int []){x * 25, dest.x1 * 25}, (int []){y * 25, dest.y1 * 25}, img);
	// 		dest.x1 = get_dest(x, y + 1, ft_atoi(cor[y][x]), 1);
	// 		dest.y1 = get_dest(x, y + 1, ft_atoi(cor[y][x]), 0);
	// 		drawline_v((int []){x * 25, dest.x1 * 25}, (int []){y * 25, dest.y1 * 25}, img);
	// 		x++;
	// 	}
	// 	y++;
	// }
	int	tmpx;
	int	tmpy;
	while (y <= 300)
	{
		x = 0;
		while (x <= 300)
		{
			// tmpx = get_dest(x + 10, y, 0, 1);
			// tmpy = get_dest(x, y + 10, 0, 0);
			drawline_h((int []){x, x + 10}, (int []){y, y}, img);
			drawline_v((int []){x, x}, (int []){y, y + 10}, img);
			x += 10;
		}
		y += 10;
	}
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
	// 		drawline_h((double []){0 * 4, 20 * 4}, (double []){20 * 4, 20 * 4}, img);
	// 		drawline_v((double []){20 * 4, 20 * 4}, (double []){0 * 4, 20 * 4}, img);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// drawline_h((double []){0, 4 * 25}, (double []){0, 0}, img);
	// drawline_v((double []){0, j * 25}, (double []){0, (i + 1) * 25}, img);
}

void	first(char ***cor)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 920, 920, "first test");
	img.img = mlx_new_image(mlx, 920, 920);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	plot(cor, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 20, 20);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, mlx_win);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	***cor;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror(argv[1]), 1);
	cor = grap_input(argv[1], fd);
	close(fd);
	first(cor);
	free_cor(cor);
	argc -= 1;
	return (argc);
}

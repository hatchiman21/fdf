/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/28 07:23:48 by aatieh           ###   ########.fr       */
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

int	free_points(t_point *point)
{
	t_point	*tmp;
	t_point	*tmp2;

	if (!point)
		return (0);
	tmp = point->next_y;
	while (point)
	{
		tmp2 = point->next_x;
		free(point);
		if (tmp2)
			point = tmp2;
		else
		{
			point = tmp;
			if (tmp)
				tmp = tmp->next_y;
		}
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
			ft_printf("%d ",ft_atoi(cor[i][j++]));
		i++;
		ft_printf("\n");
	}
}

void	print_lines(t_point *point)
{
	t_point	*next_row;
	t_point	*tmp_x;
	t_point	*tmp_y;

	if (!point)
		return ;
	next_row = point->next_y;
	while (point)
	{
		ft_printf("\n");
		tmp_x = point->next_x;
		tmp_y = point->next_y;
		if (tmp_x)
			ft_printf("{(%d, %d), (%d, %d)]\n",point->x, point->y, tmp_x->x, tmp_x->y);
		if (tmp_y)
			ft_printf("{(%d, %d), (%d, %d)]\n",point->x, point->y, tmp_y->x, tmp_y->y);
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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel) / 8);
	*(unsigned int *)dst = color;
}
/*
drawline_h if ∣dx∣>∣dy∣
*/

int	get_dest(int x, int y, int z, int is_x)
{
	double	a;
	double	res;

	// a = (2.0 * PI) / 3.0;
	// if (is_x)
	// 	res = x * cos(a) + y * cos(a + 2) + z * cos(a - 2);
	// else
	// 	res = x * sin(a) + y * sin(a + 2) + z * sin(a - 2);
	// if (is_x)
	// 	res = (x - z) / sqrt(2);
	// else
	// 	res = (x + 2 * y + z ) / sqrt(6);
	int tmp;

	tmp = x;
	if (is_x)
		res = (tmp - y) * cos(0.523599);
	else
		res = (tmp + y) * sin(0.523599) - z;
	// ft_printf("x is %d, y is %d res is %d\n", x, y, (int)round(res));
	// if (is_x)
	// 	res = x - y;
	// else
	// 	res = ((x + y) / 2) - z;
	return ((int)round(res));
}

int	get_scale(t_point *res)
{
	int		scale;
	t_point	*tmp;

	scale = 25;
	tmp = res->next_y;
	while (res)
	{
		while (res->x * scale > 900)
			scale -= 1;
		while (res->y * scale > 900)
			scale -= 1;
		while (res->next_y && res->next_y->x * scale > 900)
			scale -= 1;
		while (res->next_x && res->next_x->x * scale > 900)
			scale -= 1;
		if (!res->next_x)
		{
			res = tmp;
			if (tmp)
				tmp = tmp->next_y;
		}
		else
			res = res->next_x;
	}
	return (scale);
}

void	compare(t_point *res, int *offset)
{
	t_point	*tmp;

	tmp = res->next_y;
	while (res)
	{
		if (res->x < *offset)
			*offset = res->x;
		if (res->y < *offset)
			*offset = res->y;
		if (res->next_x)
			res = res->next_x;
		else
		{
			res = tmp;
			if (tmp)
				tmp = tmp->next_y;
		}
	}
}

	// t_point	*tmp;

	// tmp = res->next_y;
	// while (res)
	// {
	// 	res->x -= offset;
	// 	res->y -= offset;
	// 	if (res->next_x)
	// 		res = res->next_x;
	// 	else
	// 	{
	// 		res = tmp;
	// 		if (tmp)
	// 			tmp = tmp->next_y;
	// 	}
	// }
// void adjust_coordinates(t_point *res, int offset)
// {
//     t_point *row_start = res; // Start of the current row
//     t_point *current;

//     while (row_start) // Traverse rows (next_y)
//     {
//         current = row_start; // Start at the beginning of the row
//         while (current) // Traverse columns (next_x)
//         {
//             current->x -= offset;
//             current->y -= offset;
//             current = current->next_x;
//         }
//         row_start = row_start->next_y; // Move to the next row
//     }
// }

void	adjust_coordinates(t_point *res, int offset)
{
	t_point	*tmp;

	tmp = res->next_y;
	while (res)
	{
		while (res)
		{
			res->x -= offset;
			res->y -= offset;
			res = res->next_x;
		}
		res = tmp;
		if (tmp)
			tmp = tmp->next_y;
	}
}
void print_points(t_point *res)
{
    t_point *row_start = res;
    t_point *current;

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


void	shift(t_point *res)
{
	int		offset;
	t_point	*tmp;
	t_point	*tmp2;

	offset = 0;
	tmp = res;
	tmp2 = tmp->next_y;
	while (tmp)
	{
		compare(tmp, &offset);
		if (tmp->next_y)
			compare(tmp->next_y, &offset);
		if (tmp->next_x)
			tmp = tmp->next_x;
		else
		{
			tmp = NULL;
			if (tmp2)
			{
				tmp = tmp2->next_x;
				tmp2 = tmp2->next_y;
			}
		}
	}
	// ft_printf("offset is %d\n", offset);
	adjust_coordinates(res, offset);
	// print_lines(res);
}

t_point	*get_node(int x, int y, int z)
{
	t_point	*node;

	node = malloc(sizeof(t_point));
	if (!node)
		return (NULL);
	node->x = get_dest(x, y, z, 1);
	node->y = get_dest(x, y, z, 0);
	node->z = z;
	node->next_x = NULL;
	node->next_y = NULL;
	return (node);
}

void	create_point_grid_step(char ***cor, t_data *img, int y, t_point **node)
{
	t_point	*prev_node;
	int		x;

	x = 0;
	prev_node = NULL;
	while (cor[y][x])
	{
		if (!((*node)->next_x) && cor[y][x + 1])
			(*node)->next_x = get_node(x + 1, y, ft_atoi(cor[y][x + 1]));
		if (cor[y + 1])
			(*node)->next_y = get_node(x, y + 1, ft_atoi(cor[y + 1][x]));
		if (prev_node && (*node)->next_y)
			prev_node->next_y->next_x = (*node)->next_y;
		prev_node = (*node);
		(*node) = (*node)->next_x;
		// ft_printf("x is %d\n", x);
		x++;
	}
}

t_point	*create_point_grid(char ***cor, t_data *img)
{
	t_point	*res;
	t_point	*node;
	int		y;

	res = get_node(0, 0, ft_atoi(cor[0][0]));
	node = res;
	y = 0;
	while (cor[y])
	{
		create_point_grid_step(cor, img, y, &node);
		node = res;
		while (node && node->next_y)
			node = node->next_y;
		// ft_printf("y is %d\n", y);
		y++;
	}
	return (res);
}
	// ft_printf("scale is %d\n", scale);
	// next_row = res->next_y;
	// while (res)
	// {
	// 	if (res->next_y)
	// 		drawline_dda((int []){res->x, res->next_y->x},
	// 			(int []){res->y, res->next_y->y}, img);
	// 	if (res->next_x)
	// 		drawline_dda((int []){res->x, res->next_x->x},
	// 			(int []){res->y, res->next_x->y}, img);
	// 	else
	// 	{
	// 		res = next_row;
	// 		if (next_row)
	// 			next_row = next_row->next_y;
	// 	}
	// }

void	draw(char ***cor, t_point *res, t_data *img)
{
	int		scale;
	t_point	*next_row;

	scale = get_scale(res);
	next_row = res->next_y;
	while (res)
	{
		if (res->next_y)
			drawline_v((int []){res->x * scale, res->next_y->x * scale},
				(int []){res->y * scale, res->next_y->y * scale}, img);
		if (res->next_x)
		{
			drawline_h((int []){res->x * scale, res->next_x->x * scale},
				(int []){res->y * scale, res->next_x->y * scale}, img);	
			res = res->next_x;
		}
		else
		{
			res = next_row;
			if (next_row)
				next_row = next_row->next_y;
		}
	}
}

void	first(char ***cor)
{
	t_point	*res;
	t_data	img;

	if (cor[0])
	res = create_point_grid(cor, &img);
	if (!res)
	{
		ft_dprintf(2, "Malloc failed\n");
		exit(3);
	}
	// print_lines(res);
	shift(res);
	// print_lines(res);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 920, 920, "first test");
	img.img = mlx_new_image(img.mlx, 920, 920);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	draw(cor, res, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 20, 20);
	mlx_loop(img.mlx);
	mlx_destroy_window(img.mlx, img.win);
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

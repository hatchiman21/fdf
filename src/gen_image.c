/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_2d_map.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:34:10 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 00:48:35 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

void	offeset_map_step(t_point *point, int offset)
{
	t_point	*tmp;

	tmp = point->next_y;
	while (point)
	{
		while (point)
		{
			point->x -= offset;
			point->y -= offset;
			point = point->next_x;
		}
		point = tmp;
		if (tmp)
			tmp = tmp->next_y;
	}
}

void	offset_map(t_point *first_point, t_var *var)
{
	int		offset;
	t_point	*tmp;
	t_point	*tmp2;

	offset = 0;
	tmp = first_point;
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
	offeset_map_step(first_point, offset);
}

// int	gen_2d_line(int *x, int *y, int *z, t_line **res)
// {
// 	t_line	*node;
// 	int		scale;

// 	scale = 100;
// 	node = malloc(sizeof(t_line));
// 	if (!node)
// 		return (0);
// 	if (*res != NULL)
// 	{
// 		while ((*res)->next)
// 			*res = (*res)->next;
// 		(*res)->next = node;
// 	}
// 	else
// 		*res = node;
// 	node->next = NULL;
// 	node->x0 = get_point(x[0] * scale, y[0] * scale, z[0] * scale, 1);
// 	node->y0 = get_point(x[0] * scale, y[0] * scale, z[0] * scale, 0);
// 	node->x1 = get_point(x[1] * scale, y[1] * scale, z[1] * scale, 1);
// 	node->y1 = get_point(x[1] * scale, y[1] * scale, z[1] * scale, 0);
// 	node->z0 = z[0];
// 	node->z1 = z[1];
// 	return (1);
// }

void	create_connect_node(char ***map,  t_point **node, int y, t_data *img)
{
	t_point	*prev_node;
	int		x;
	int		scale_up;

	x = 0;
	scale_up = 100;
	prev_node = NULL;
	while (map[y][x])
	{
		if (!((*node)->next_x) && map[y][x + 1])
			(*node)->next_x = get_node((x + 1) * scale_up, y * scale_up, ft_atoi(map[y][x + 1]) * scale_up);
		if (map[y + 1])
			(*node)->next_y = get_node(x * scale_up, (y + 1) * scale_up, ft_atoi(map[y + 1][x]) * scale_up);
		if (prev_node && (*node)->next_y)
			prev_node->next_y->next_x = (*node)->next_y;
		prev_node = (*node);
		(*node) = (*node)->next_x;
		x++;
	}
}

t_point	*gen_2d_map(char ***map, t_data *img)
{
	t_point	*res;
	t_point	*node;
	int		y;

	res = get_node(0, 0, ft_atoi(map[0][0]) * 100);
	node = res;
	y = 0;
	while (map[y])
	{
		create_connect_node(map, &node, y,  img);
		node = res;
		while (node && node->next_y)
			node = node->next_y;
		y++;
	}
	return (res);
}

// t_point	*gen_2d_map(char ***cor, t_data *img)
// {
// 	t_point	*res;
// 	t_point	*tmp;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	tmp = NULL;
// 	res = NULL;
// 	while (cor[y])
// 	{
// 		x = 0;
// 		while (cor[y][x])
// 		{
// 			if (cor[y + 1] && ft_isdigit(cor[y + 1][x][0])
// 				&& !gen_2d_line((int []){x, x}, (int []){y, (y + 1)}
// 				, (int []){ft_atoi(cor[y][x]), ft_atoi(cor[y + 1][x])}, &tmp))
// 					return (free_lines(res));
// 			if (res == NULL && tmp) 
// 				res = tmp;
// 			if (cor[y][x + 1] && ft_isdigit(cor[y][x + 1][0])
// 				&& !gen_2d_line((int []){x, (x + 1)}, (int []){y, y}
// 				, (int []){ft_atoi(cor[y][x]), ft_atoi(cor[y][x + 1])}, &tmp))
// 				return (free_lines(res));
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (res);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:36:22 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 03:12:21 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	get_offset(t_point *lst, int *offset)
{
	if (lst->x < *offset)
		*offset = lst->x;
	if (lst->y < *offset)
		*offset = lst->y;
}

int	get_point(int x, int y, int z, int is_x)
{
	int	res;

	res = 0;
	if (is_x)
		res = x - y;
	else
		res = ((x + y) / 2) - z;
	return (res);
}

t_point	*get_node(int x, int y, int z)
{
	t_point	*node;

	node = malloc(sizeof(t_point));
	if (!node)
		return (NULL);
	node->x = get_point(x, y, z, 1);
	node->y = get_point(x, y, z, 0);
	node->z = z;
	node->next_x = NULL;
	node->next_y = NULL;
	return (node);
}

float	get_scale(t_point *point, t_var	*vars)
{
	float	scale;
	t_point	*tmp;
	t_point	*tmp2;

	scale = 1;
	tmp = point->next_y;
	while (point)
	{
		tmp2 = point->next_x;
		while (point->x * scale > vars->width)
			scale -= 0.0005;
		while (point->y * scale > vars->height)
			scale -= 0.0005;
		if (tmp2)
			point = tmp2;
		else
		{
			point = tmp;
			if (tmp)
				tmp = tmp->next_y;
		}
	}
	return (scale);
}

t_height	min_max_height(t_point *point)
{
	t_point		*tmp;
	t_point		*tmp2;
	t_height	height;
	
	height.max = 0;
	height.min = 0;
	tmp = point->next_y;
	while (point)
	{
		tmp2 = point->next_x;
		if (point->z > height.max)
			height.max = point->z;
		else
			height.min = point->z;
		if (tmp2)
			point = tmp2;
		else
		{
			point = tmp;
			if (tmp)
				tmp = tmp->next_y;
		}
	}
	return (height);
}

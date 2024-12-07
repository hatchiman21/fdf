/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:34:10 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/07 11:45:55 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	shift(t_line *res, t_var vars)
{
	int		offset;
	t_line	*tmp;

	offset = 0;
	tmp = res;
	while (tmp)
	{
		get_offset(tmp, &offset);
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
	int		scale;

	scale = 100;
	node = malloc(sizeof(t_line));
	if (!node)
		return (0);
	if (*res != NULL)
	{
		while ((*res)->next)
			*res = (*res)->next;
		(*res)->next = node;
	}
	else
		*res = node;
	node->next = NULL;
	node->x0 = get_dest(x[0] * scale, y[0] * scale, z[0] * scale, 1);
	node->y0 = get_dest(x[0] * scale, y[0] * scale, z[0] * scale, 0);
	node->x1 = get_dest(x[1] * scale, y[1] * scale, z[1] * scale, 1);
	node->y1 = get_dest(x[1] * scale, y[1] * scale, z[1] * scale, 0);
	node->z0 = z[0];
	node->z1 = z[1];
	return (1);
}

t_line	*plot(char ***cor, t_data *img)
{
	t_line	*res;
	t_line	*tmp;
	int		y;
	int		x;

	y = 0;
	tmp = NULL;
	res = NULL;
	while (cor[y])
	{
		x = 0;
		while (cor[y][x])
		{
			if (cor[y + 1] && ft_isdigit(cor[y + 1][x][0])
				&& !get_res((int []){x, x}, (int []){y, (y + 1)}
				, (int []){ft_atoi(cor[y][x]), ft_atoi(cor[y + 1][x])}, &tmp))
					return (free_lines(res));
			if (res == NULL && tmp) 
				res = tmp;
			if (cor[y][x + 1] && ft_isdigit(cor[y][x + 1][0])
				&& !get_res((int []){x, (x + 1)}, (int []){y, y}
				, (int []){ft_atoi(cor[y][x]), ft_atoi(cor[y][x + 1])}, &tmp))
				return (free_lines(res));
			x++;
		}
		y++;
	}
	return (res);
}

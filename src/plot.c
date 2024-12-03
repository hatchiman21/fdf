/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:34:10 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/03 21:32:32 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	shift(t_line *res)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/25 21:55:41 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Now we have the image address, but still no pixels.Before we start with this
// , we must understand that the bytes are not aligned,
// this means that the line_length differs from the actual window width.
// We therefore should ALWAYS calculate the memory offset using the line length set by mlx_get_data_addr.
// We can calculate it very easily by using the following formula:
// int offset = (y * line_length + x * (bits_per_pixel / 8));

static int	swap(int *x0, int *y0, int *x1, int *y1)
{
	int	tmp;

	if (*x0 > *x1)
	{
		tmp = *x0;
		*x0 = *x1;
		*x1 = tmp;
		tmp = *y0;
		*y0 = *y1;
		*y1 = tmp;
	}
	if (*y0 > *y1)
		return (-1);
	return (1);
}

// void	drawline_h(int *x, int *y, t_data *img)
// {
// 	int	p;
// 	int	i;
// 	int	dx;
// 	int	dy;
// 	int dir;

// 	i = -1;
// 	dir = swap(&x[0], &y[0], &x[1], &y[1]);
// 	dx = x[1] - x[0];
// 	dy = ABS(y[1] - y[0]);
// 	if (dx == 0)
// 		return ;
// 	p = 2 * dy - dx;
// 	while (i++ <= dx)
// 	{
// 		my_mlx_pixel_put(img, x[0] + i, y[0], 0xFF0000);
// 		if (p >= 0)
// 		{
// 			y[0] += dir;
// 			p -= 2 * dx;
// 		}
// 		else
// 			p += 2 * dy;
// 	}
// }

void	drawline_v(int *x, int *y, t_data *img)
{
	double	y;
	int		i;

	y = (double)y[0];
	swap(&y[0], &x[0], &y[1], &x[1]);
	i = 0;
	while (i < (x[1] - x[0]))
	{
		my_mlx_pixel_put(img, x[0] + i, (int)round(y), 0xFF0000);
		// y = (double)(y[0] * (x[1] - x[0] - i) + y[1] * i) / (double)(x[1] - x[0]);
		y = (double)((double)((x[0] + i - x[1]) * (y[1] - y[0])) / (x[1] - x[0])) + (double)y[0];
		i++;
	}
}

// void	drawline_v(int *x, int *y, t_data *img)
// {
// 	int	p;
// 	int	i;
// 	int dx;
// 	int dy;
// 	int	dir;

// 	i = 0;
// 	dir = swap(&y[0], &x[0], &y[1], &x[1]);
// 	dx = (x[1] - x[0]) * dir;
// 	dy = y[1] - y[0];
// 	if (dy == 0)
// 		return ;
// 	p = 2 * dx - dy;
// 	while (i <= dy)
// 	{
// 		my_mlx_pixel_put(img, x[0], y[0] + i, 0xFF0000);
// 		if (p >= 0)
// 		{
// 			x[0] += dir;
// 			p -= 2 * dy;
// 		}
// 		else
// 			p += 2 * dx;
// 		i++;
// 	}
// }

void	drawline_h(int *x, int *y, t_data *img)
{
	double	x;
	int		i;

	x = (double)x[0];
	swap(&x[0], &y[0], &x[1], &y[1]);
	i = 0;
	while (i < (y[1] - y[0]))
	{
		my_mlx_pixel_put(img, (int)round(x), y[0] + i, 0xFF0000);
		// x = (double)(y[0] * (x[1] - x[0] - i) + y[1] * i) / (double)(x[1] - x[0]);
		x = (double)((double)(i * (x[1] - x[0]) / (y[1] = y[0])) / (y[1] - y[0])) + (double)x[0]
		i++;
	}
}

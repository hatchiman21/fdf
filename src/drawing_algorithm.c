/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/28 07:28:57 by aatieh           ###   ########.fr       */
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

// void	drawline_v(int *x, int *y, t_data *img)
// {
// 	double	y2;
// 	int		i;

// 	y2 = (double)y[0];
// 	swap(&y[0], &x[0], &y[1], &x[1]);
// 	i = 0;
// 	while (i < (x[1] - x[0]))
// 	{
// 		my_mlx_pixel_put(img, x[0] + i, (int)round(y2), 0xFF0000);
// 		// y = (double)(y[0] * (x[1] - x[0] - i) + y[1] * i) / (double)(x[1] - x[0]);
// 		y2 = (double)((double)((x[0] + i - x[1]) * (y[1] - y[0])) / (x[1] - x[0])) + (double)y[0];
// 		i++;
// 	}
// }

// void drawline_v(int *x, int *y, t_data *img)
// {
// 	int dx, dy, p, x2, y2, x_end;

// 	dx = ABS(x[1] - x[0]);
// 	dy = ABS(y[1] - y[0]);
// 	p = 2 * dy - dx;
// 	if (x[0] > x[1]) {
// 		x2 = x[1];
// 		y2 = y[1];
// 		x_end = x[0];
// 	} else {
// 		x2 = x[0];
// 		y2 = y[0];
// 		x_end = x[1];
// 	}
// 	my_mlx_pixel_put(img, x2, y2, 0xFF0000);
// 	while (x2 < x_end) {
// 		x2++;
// 		if (p < 0) {
// 			p = p + 2 * dy;
// 		} else {
// 			y2 += (y[1] > y[0]) ? 1 : -1;
// 			p = p + 2 * dy - 2 * dx;
// 		}
// 		my_mlx_pixel_put(img, x2, y2, 5);
// 	}
// }

// void drawline_h(int *x, int *y, t_data *img)
// {
// 	int dx, dy, p, x2, y2, y_end;

// 	dx = ABS(x[1] - x[0]);
// 	dy = ABS(y[1] - y[0]);
// 	p = 2 * dx - dy;
// 	if (y[0] > y[1]) {
// 		x2 = x[1];
// 		y2 = y[1];
// 		y_end = y[0];
// 	} else {
// 		x2 = x[0];
// 		y2 = y[0];
// 		y_end = y[1];
// 	}
// 	my_mlx_pixel_put(img, x2, y2, 0xFF0000);
// 	while (y2 < y_end) {
// 		y2++;
// 		if (p < 0) {
// 			p = p + 2 * dx;
// 		} else {
// 			x2 += (x[1] > x[0]) ? 1 : -1;
// 			p = p + 2 * dx - 2 * dy;
// 		}
// 		my_mlx_pixel_put(img, x2, y2, 10);
// 	}
// }

void drawline_all(int *x, int *y, t_data *img)
{
	double	t;
	int		i;
	int		x2;
	int		y2;

	i = 0;
	while (i <= ABS(x[1] - x[0]))
	{
		t = (double)i / (double)ABS(x[1] - x[0]);
		x2 = (int)round((double)x[0] + t * (double)(x[1] - x[0]));
		y2 = (int)round((double)y[0] + t * (double)(y[1] - y[0]));
		my_mlx_pixel_put(img, x2, y2, 0xFF0000);
		i++;
	}
}

void	drawline_dda(int *x, int *y, t_data *img)
{
	double	steps;
	double	x_inc;
	double	y_inc;
	double	x2;
	double	y2;
	int		i;

	if (ABS(x[1] - x[0]) > ABS(y[1] - y[0]))
		steps = ABS(x[1] - x[0]);
	else
		steps = ABS(y[1] - y[0]);
	x_inc = (x[1] - x[0]) / steps;
	y_inc = (y[1] - y[0]) / steps;
	x2 = x[0];
	y2 = y[0];
	i = 0;
	while (i <= steps)
	{
		x2 += x_inc;
		y2 += y_inc;
		my_mlx_pixel_put(img, (int)round(x2), (int)round(y2), 0xFF0000);
		i++;
	}
	// x[1] = x2;
	// y[1] = y2;
}

void	drawline_h(int *x, int *y, t_data *img)
{
	int dir;
	int p;
	int i;
	int y_tmp;

	i = 0;
	if (x[1] - x[0] == 0)
		return;
	dir = swap(&x[0], &y[0], &x[1], &y[1]);
	p = 2 * (y[1] - y[0]) * dir - (x[1] - x[0]);
	y_tmp = y[0];
	while (i <= (x[1] - x[0]))
	{
		my_mlx_pixel_put(img, x[0] + i, y_tmp, 0x00FF0000);
		if (p >= 0)
		{
			y_tmp += dir;
			p -= 2 * (x[1] - x[0]);
		}
		else
			p += 2 * (y[1] - y[0]) * dir;
		i++;
	}
}

void	drawline_v(int *x, int *y, t_data *img)
{
	int	p;
	int	i;
	int	x_end;
	int	dir;

	i = 0;
	dir = swap(&y[0], &x[0], &y[1], &x[1]);
	if ((y[1] - y[0]) == 0)
		return ;
	p = 2 * (x[1] - x[0]) * dir - (y[1] - y[0]);
	x_end = x[0];
	while (i <= (y[1] - y[0]))
	{
		my_mlx_pixel_put(img, x_end, y[0] + i, 0xFF0000);
		if (p >= 0)
		{
			x_end += dir;
			p -= 2 * (y[1] - y[0]);
		}
		else
			p += 2 * (x[1] - x[0]) * dir;
		i++;
	}
}

// void	drawline_h(int *x, int *y, t_data *img)
// {
// 	double	x2;
// 	int		i;

// 	x2 = (double)x[0];
// 	swap(&x[0], &y[0], &x[1], &y[1]);
// 	i = 0;
// 	while (i < (y[1] - y[0]))
// 	{
// 		my_mlx_pixel_put(img, (int)round(x2), y[0] + i, 0xFF0000);
// 		// x = (double)(y[0] * (x[1] - x[0] - i) + y[1] * i) / (double)(x[1] - x[0]);
// 		x2 = (double)((double)(i * (x[1] - x[0]) / (y[1] = y[0])) / (y[1] - y[0])) + (double)x[0];
// 		i++;
// 	}
// }

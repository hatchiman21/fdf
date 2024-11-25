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

// void	drawline_h(double *x_start, double *y_start, t_data *img)
// {
// 	int		dir;
// 	double	p;
// 	double	i;
// 	double	y;

// 	i = 0;
// 	if ((x_start[1] - x_start[0]) == 0)
// 		return ;
// 	dir = swap(&x_start[0], &y_start[0], &x_start[1], &y_start[1]);
// 	p = 2.0 * (y_start[1] - y_start[0]) * dir - (x_start[1] - x_start[0]);
// 	y = y_start[0];
// 	while (i <= (x_start[1] - x_start[0]))
// 	{
// 		my_mlx_pixel_put(img, x_start[0] + i, round(y), 0xFF0000);
// 		if (p >= 0)
// 		{
// 			y += dir;
// 			p -= 2.0 * (x_start[1] - x_start[0]);
// 		}
// 		else
// 			p += 2.0 * (y_start[1] - y_start[0]) * dir;
// 		i++;
// 	}
// }

// void	drawline_h(int *x_start, int *y_start, t_data *img)
// {
// 	int	p;
// 	int	i;
// 	int	y;

// 	i = 0;
// 	if (x_start[1] - x_start[0] == 0)
// 		return ;
// 	swap(&x_start[0], &y_start[0], &x_start[1], &y_start[1]);
// 	p = 2 * ABS(y_start[1] - y_start[0]) - (x_start[1] - x_start[0]);
// 	y = y_start[0];
// 	while (i <= (x_start[1] - x_start[0]))
// 	{
// 		ft_printf("drawn x is %d, y is %d\n", x_start[0] + i, y);
// 		my_mlx_pixel_put(img, x_start[0] + i, y, 0xFF0000);
// 		if (p >= 0)
// 		{
// 			y += 1;
// 			p -= 2 * (x_start[1] - x_start[0]);
// 		}
// 		else
// 			p += 2 * ABS(y_start[1] - y_start[0]);
// 		i++;
// 	}
// 	ft_printf("drawn x is %d, y is %d\n", x_start[0] + i, y);
// }

void	drawline_h(int *x, int *y, t_data *img)
{
	int	p;
	int	i;
	int	dx;
	int	dy;
	int dir;

	i = -1;
	dir = swap(&x[0], &y[0], &x[1], &y[1]);
	dx = x[1] - x[0];
	dy = ABS(y[1] - y[0]);
	if (dx == 0)
		return ;
	p = 2 * dy - dx;
	while (i++ <= dx)
	{
		my_mlx_pixel_put(img, x[0] + i, y[0], 0xFF0000);
		if (p >= 0)
		{
			y[0] += dir;
			p -= 2 * dx;
		}
		else
			p += 2 * dy;
	}
}

// void	drawline_h(double *x_int, double *y_int, t_data *img)
// {
// 	int		dir;
// 	double	p;
// 	double	i;
// 	double	y;

// 	i = 0;
// 	if ((x_int[1] - x_int[0]) == 0)
// 		return ;
// 	dir = swap(&x_int[0], &y_int[0], &x_int[1], &y_int[1]);
// 	p = 2 * (y_int[1] - y_int[0]) * dir - (x_int[1] - x_int[0]);
// 	y = y_int[0];
// 	while (i <= (x_int[1] - x_int[0]))
// 	{
// 		my_mlx_pixel_put(img, y, x_int[0] + i, 0x00FF0000);
// 		if (p >= 0)
// 		{
// 			y += dir;
// 			p -= 2 * (x_int[1] - x_int[0]);
// 		}
// 		else
// 			p += 2 * (y_int[1] - y_int[0]) * dir;
// 		i++;
// 	}
// }

void	drawline_v(int *x, int *y, t_data *img)
{
	int	p;
	int	i;
	int dx;
	int dy;
	int	dir;

	i = 0;
	dir = swap(&y[0], &x[0], &y[1], &x[1]);
	dx = (x[1] - x[0]) * dir;
	dy = y[1] - y[0];
	if (dy == 0)
		return ;
	p = 2 * dx - dy;
	while (i <= dy)
	{
		my_mlx_pixel_put(img, x[0], y[0] + i, 0xFF0000);
		if (p >= 0)
		{
			x[0] += dir;
			p -= 2 * dy;
		}
		else
			p += 2 * dx;
		i++;
	}
}

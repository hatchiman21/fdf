/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/22 05:37:24 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Now we have the image address, but still no pixels.Before we start with this
// , we must understand that the bytes are not aligned,
// this means that the line_length differs from the actual window width.
// We therefore should ALWAYS calculate the memory offset using the line length set by mlx_get_data_addr.
// We can calculate it very easily by using the following formula:
// int offset = (y * line_length + x * (bits_per_pixel / 8));

static int	swap_sign(int *x0, int *y0, int *x1, int *y1)
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
	if ((*y1 - *y0) < 0)
		tmp = -1;
	else
		tmp = 1;
	return (tmp);
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
// 	dir = swap_sign(&x_start[0], &y_start[0], &x_start[1], &y_start[1]);
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

void	drawline_h(int *x_start, int *y_start, t_data *img)
{
	int dir;
	int p;
	int i;
	int y;

	i = 0;
	if (x_start[1] - x_start[0] == 0)
		return;
	dir = swap_sign(&x_start[0], &y_start[0], &x_start[1], &y_start[1]);
	p = 2 * (y_start[1] - y_start[0]) * dir - (x_start[1] - x_start[0]);
	y = y_start[0];
	while (i <= (x_start[1] - x_start[0]))
	{
		my_mlx_pixel_put(img, x_start[0] + i, y, 0xFF0000);
		if (p >= 0)
		{
			y += dir;
			p -= 2 * (x_start[1] - x_start[0]);
		}
		else
			p += 2 * (y_start[1] - y_start[0]) * dir;
		i++;
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
// 	dir = swap_sign(&x_int[0], &y_int[0], &x_int[1], &y_int[1]);
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

void	drawline_v(int *x_int, int *y_int, t_data *img)
{
	int		dir;
	int	p;
	int	i;
	int	x;

	i = 0;
	if ((y_int[1] - y_int[0]) == 0)
		return ;
	dir = swap_sign(&y_int[0], &x_int[0], &y_int[1], &x_int[1]);
	p = 2 * (x_int[1] - x_int[0]) * dir - (y_int[1] - y_int[0]);
	x = x_int[0];
	while (i <= (y_int[1] - y_int[0]))
	{
		my_mlx_pixel_put(img, x, y_int[0] + i, 0x00FF0000);
		if (p >= 0)
		{
			x += dir;
			p -= 2 * (y_int[1] - y_int[0]);
		}
		else
			p += 2 * (x_int[1] - x_int[0]) * dir;
		i++;
	}
}

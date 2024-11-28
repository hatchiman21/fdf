/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:15 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/28 22:00:47 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Now we have the image address, but still no pixels.Before we start with this
// , we must understand that the bytes are not aligned,
// this means that the line_length differs from the actual window width.
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

void drawline_v(int *x, int *y, t_data *img)
{
	int dx, dy, p, x2, y2, x_end;

	dx = ABS(x[1] - x[0]);
	dy = ABS(y[1] - y[0]);
	p = 2 * dy - dx;
	if (x[0] > x[1]) {
		x2 = x[1];
		y2 = y[1];
		x_end = x[0];
	} else {
		x2 = x[0];
		y2 = y[0];
		x_end = x[1];
	}
	my_mlx_pixel_put(img, x2, y2, 0xFF0000);
	while (x2 < x_end) {
		x2++;
		if (p < 0) {
			p = p + 2 * dy;
		} else {
			y2 += (y[1] > y[0]) ? 1 : -1;
			p = p + 2 * dy - 2 * dx;
		}
		my_mlx_pixel_put(img, x2, y2, 5);
	}
}

void drawline_h(int *x, int *y, t_data *img)
{
	int dx, dy, p, x2, y2, y_end;

	dx = ABS(x[1] - x[0]);
	dy = ABS(y[1] - y[0]);
	p = 2 * dx - dy;
	if (y[0] > y[1]) {
		x2 = x[1];
		y2 = y[1];
		y_end = y[0];
	} else {
		x2 = x[0];
		y2 = y[0];
		y_end = y[1];
	}
	my_mlx_pixel_put(img, x2, y2, 0xFF0000);
	while (y2 < y_end) {
		y2++;
		if (p < 0) {
			p = p + 2 * dx;
		} else {
			x2 += (x[1] > x[0]) ? 1 : -1;
			p = p + 2 * dx - 2 * dy;
		}
		my_mlx_pixel_put(img, x2, y2, 10);
	}
}

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

// void	drawline_test(int *x, int *y, t_data *img)
// {
// 	int dx;
// 	int dy;
// 	int p;
// 	int x_tmp;
// 	int y_tmp;
	
// 	dx = x[1] - x[0];
// 	dy = y[1] - y[0];
// 	x_tmp = x[0];
// 	y_tmp = y[0];
// 	p = 2 * dy - dx;
// 	while (x_tmp < x[1])
// 	{
// 		if (p >= 0)
// 		{
// 			my_mlx_pixel_put(img, x_tmp, y_tmp, 0xFF0000);
// 			y_tmp += 1;
// 			p = p + 2 * dy - 2 * dx;
// 		}
// 		else
// 		{
// 			my_mlx_pixel_put(img, x_tmp, y_tmp, 0xFF0000);
// 			p = p + 2 * dy;
// 		}
// 		x_tmp += 1;
// 	}
// }

// void	drawline_test(int *x, int *y, t_data *img)
// {
// 	int m_new = 2 * (y[1] - y[0]);
// 	int slope_error_new = m_new - (x[1] - x[0]);
// 	int x_tmp, y_tmp;

// 	for (x_tmp = x[0], y_tmp = y[0]; x_tmp <= x[1]; x++)
// 	{
// 		my_mlx_pixel_put(img, x_tmp, y_tmp, 0xFF0000);
// 		slope_error_new += m_new;
// 		if (slope_error_new >= 0)
// 		{
// 			y++;
// 			slope_error_new -= 2 * (x[1] - x[0]);
// 		}
// 	}
// }

// void	drawline_test(int *x, int *y, t_data *img)
// {
// 	int dy;
// 	int dx;
// 	int d;
// 	int x_tmp;
// 	int y_tmp;

// 	dy = y[1] - y[0];
// 	dx = x[1] - x[0];
// 	d = 2 * dy - dx;
// 	x_tmp = x[0];
// 	y_tmp = y[0];
// 	while (x_tmp <= x[1])
// 	{
// 		my_mlx_pixel_put(img, x_tmp, y_tmp, 0xFF0000);
// 		x_tmp += 1;
// 		if (d < 0)
// 			d += 2 * dy;
// 		else
// 		{
// 			d += 2 * (dy - dx);
// 			y += 1;
// 		}
// 	}
// }

// void	drawline_test(int *x, int *y, t_data *img)
// {
// 	int w = x[1] - x[0];
// 	int h = y[1] - y[0];
// 	int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;

// 	if (w < 0)
// 		dx1 = -1;
// 	else if (w > 0)
// 		dx1 = 1;
// 	if (h < 0)
// 		dy1 = -1;
// 	else if (h > 0)
// 		dy1 = 1;
// 	if (w < 0)
// 		dx2 = -1;
// 	else if (w > 0)
// 		dx2 = 1;
// 	int longest = ABS(w);
// 	int shortest = ABS(h);
// 	if (!(longest > shortest))
// 	{
// 		longest = ABS(h);
// 		shortest = ABS(w);
// 		if (h < 0)
// 			dy2 = -1;
// 		else if (h > 0)
// 			dy2 = 1;
// 		dx2 = 0;
// 	}
// 	int numerator = longest >> 1;
// 	for (int i = 0; i <= longest; i++)
// 	{
// 		ft_printf("x is %d and y is %d\n", x[0], y[0]);
// 		my_mlx_pixel_put(img, (x[0]), (y[0]), 0xFF0000);
// 		numerator += shortest;
// 		if (!(numerator < longest))
// 		{
// 			numerator -= longest;
// 			x += dx1;
// 			y += dy1;
// 		}
// 		else
// 		{
// 			x += dx2;
// 			y += dy2;
// 		}
// 	}
// }

#include <stdlib.h> // For abs()

void drawline_test(int *x, int *y, t_data *img)
{
    int w = x[1] - x[0];
    int h = y[1] - y[0];
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;

    if (w < 0) dx1 = -1; else if (w > 0) dx1 = 1;
    if (h < 0) dy1 = -1; else if (h > 0) dy1 = 1;
    if (w < 0) dx2 = -1; else if (w > 0) dx2 = 1;

    int longest = abs(w);
    int shortest = abs(h);

    if (!(longest > shortest)) {
        longest = abs(h);
        shortest = abs(w);
        if (h < 0) dy2 = -1; else if (h > 0) dy2 = 1;
        dx2 = 0;
    }

    int numerator = longest >> 1;
    for (int i = 0; i <= longest; i++) {
        my_mlx_pixel_put(img, ABS(x[0]), ABS(y[0]), 0xFF0000);
        numerator += shortest;
        if (!(numerator < longest)) {
            numerator -= longest;
            x[0] += dx1;
            y[0] += dy1;
        } else {
            x[0] += dx2;
            y[0] += dy2;
        }
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

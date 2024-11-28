/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:46 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/28 05:17:59 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define ABS(Value) (Value * ((Value < 0) ? -1 : 1))
# define PI 3.14159265358979323846

// typedef struct	s_data
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
typedef struct	s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	struct	s_line	*next;
}				t_line;

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
	struct	s_point	*next_x;
	struct	s_point	*next_y;
}				t_point;

typedef struct	s_res
{
	int	x;
	int	y;
}				t_res;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	drawline_v(int *x_start, int *y_start, t_data *img);
void	drawline_h(int *x_start, int *y_start, t_data *img);
void 	drawline_all(int *x, int *y, t_data *img);
void	drawline_dda(int *x, int *y, t_data *img);

#endif

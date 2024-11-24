/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:46 by aatieh            #+#    #+#             */
/*   Updated: 2024/11/24 16:15:57 by aatieh           ###   ########.fr       */
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

typedef struct	s_data
{
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

typedef struct	s_res
{
	int	x;
	int	y;
}				t_res;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	drawline_v(int *x_start, int *y_start, t_data *img);
void	drawline_h(int *x_start, int *y_start, t_data *img);

#endif

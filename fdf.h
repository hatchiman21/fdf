/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:46 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/03 02:50:10 by aatieh           ###   ########.fr       */
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

# define ABS(Value) (Value * ((Value < 0) ? 1 : -1))
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
	int	z0;
	int	z1;
	struct	s_line	*next;
}				t_line;

typedef struct	s_modifiers
{
	int	w;
	int	h;
	int	dx;
	int	dy;
}				t_modifiers;

typedef struct s_height
{
	int	min;
	int	max;
}				t_height;

typedef struct	s_res
{
	int	x;
	int	y;
}				t_res;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	drawline(t_line *res, t_height height, t_data *img);

#endif

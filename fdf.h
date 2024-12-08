/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:46 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 03:05:58 by aatieh           ###   ########.fr       */
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

# define PI 3.14159265358979323846

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
	struct	s_point	*next_x;
	struct	s_point	*next_y;
}				t_point;

typedef struct	s_var
{
	void	*mlx;
	void	*win;
	char	***map;
	t_point *point;
	t_data	img;
	int		width;
	int		height;
	float	x_angle;
	float	y_angle;
}				t_var;

typedef struct s_height
{
	int	min;
	int	max;
}				t_height;

typedef struct	s_modifiers
{
	int			w;
	int			h;
	int			dx;
	int			dy;
	t_height	height;
}				t_modifiers;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			close_win(int keycode, t_var *var);
int			close_exit(t_var *var);
void		offset_map(t_point *first_point, t_var *var);
char		***free_map(char ***string);
void		free_all(t_var *var, char ***map);
char		***grap_map(char *arg, int fd);
void		get_offset(t_point *lst, int *offset);
t_point		*get_node(int x, int y, int z);
int			get_point(int x, int y, int z, int is_x);
float		get_scale(t_point *lst, t_var *var);
t_height	min_max_height(t_point *point);
t_point		*gen_2d_map(char ***map, t_data *img);
void		drawline(t_point *point1, t_point *point2, t_height height, t_data *img);

#endif

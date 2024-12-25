/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:46 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/25 23:27:06 by aatieh           ###   ########.fr       */
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
# include <limits.h>

# define PI 3.14159265358979323846
# define WIDTH 1600
# define HEIGHT 920
# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define X 120
# define Y 121
# define Z 122
# define ISOMETRIC 1
# define PARALLEL 2

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				z0;
	int				z1;
}					t_line;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}		t_point;

typedef struct s_modifiers
{
	int	w;
	int	h;
	int	dx;
	int	dy;
	int	numerator;
}		t_modifiers;

typedef struct s_height
{
	int	min;
	int	max;
}		t_height;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}			t_mlx;

typedef struct s_var
{
	t_mlx			*mlx_win;
	char			***cor;
	int				**grid_3d;
	t_point			**grid_2d;
	t_data			img;
	float			scale;
	int				offset_x;
	int				offset_y;
	int				rows;
	int				cols;
	float			x_angle;
	float			y_angle;
	float			z_angle;
	float			*changing_angle;
	int				projection;
	int				on_display;
	t_height		height;
	struct s_var	*second;
}					t_var;

void		apply_rotation(t_var *var);
void		initialize_var(t_var *var, int projection);
void		place_image(t_var *var, t_var *tmp,
				int start_draw, int start_rotare);
void		put_pixel_to_image(t_data *data, int x, int y, int color);
void		initialize_and_draw(t_var *var, int second);
void		free_3d_map(int **map, int rows);
void		initialize_mlx(t_var *var, int second);
void		draw(t_var *var);
int			mouse_zoom(int button, int x, int y, t_var *var);
int			handle_keys(int keycode, t_var *var);
char		***free_cor(char ***string);
int			free_all(t_var *var);
int			grap_file(char *arg, t_var *var);
void		grap_3d_map(t_var *var);
t_line		calculate_line_coordinates(int i, int j, t_var *var, int vertical);
int			get_color(int height, int min_h, int max_h);
int			line_in_screen(t_line *line);
t_point		**assign_2d_grid(int rows, int cols);
void		get_bounds(t_point **map, t_height *x_h, t_height *y_h, t_var *var);
void		get_scale(t_point **map, t_var *var);
t_height	min_max_height(t_point **map, t_var *var);
void		free_2d_grid(t_point **map, int rows);
void		offset_before_scaling(t_point **map, t_var *var);

#endif

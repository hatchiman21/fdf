/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:46 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/18 15:43:32 by aatieh           ###   ########.fr       */
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
	struct s_line	*next;
}					t_line;

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

typedef struct s_var
{
	void		*mlx;
	void		*win;
	char		***cor;
	t_line		*d2_line;
	t_data		img;
	float		scale;
	int			offset_x;
	int			offset_y;
	t_height	height;
}				t_var;

void		put_pixel_to_image(t_data *data, int x, int y, int color);
void		initialize_and_draw(t_var *var);
void		draw(t_line *line, t_var *var);
int			handle_keys(int keycode, t_var *var);
int			close_exit(t_var *var);
t_line		*free_lines(t_line *lines);
char		***free_cor(char ***string);
void		free_all(t_var *var);
char		***grap_map(char *arg, int fd);
void		get_bounds(t_line *lst, t_height *x, t_height *y);
int			get_point(int x, int y, int z, int is_x);
float		get_scale(t_line *lst);
t_height	min_max_height(t_line *res);
void		offset_before_scaling(t_line *res);
t_line		*gen_2d_map(char ***cor);

#endif

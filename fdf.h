/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:46 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/13 07:23:46 by aatieh           ###   ########.fr       */
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
# define WIDTH 1600
# define HEIGHT 920
# define ESC 65307

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

typedef struct s_var
{
	void	*mlx;
	void	*win;
	char	***cor;
	t_line	*d2_line;
	t_data	img;
	float	x_angle;
	float	y_angle;
}			t_var;

typedef struct s_modifiers
{
	int	w;
	int	h;
	int	dx;
	int	dy;
}		t_modifiers;

typedef struct s_height
{
	int	min;
	int	max;
}		t_height;

void		put_pixel_to_image(t_data *data, int x, int y, int color);
void		apply_zoom_to_lines(t_line *lst, float scale);
void		initialize_and_draw(t_var *var);
void		draw(t_var *var);
int			close_win(int keycode, t_var *var);
int			close_exit(t_var *var);
t_line		*free_lines(t_line *lines);
char		***free_cor(char ***string);
void		free_all(t_var *var);
char		***grap_map(char *arg, int fd);
void		get_offset(t_line *lst, int *offset);
int			get_point(int x, int y, int z, int is_x);
float		get_scale(t_line *lst);
t_height	min_max_height(t_line *res);
void		offset_map(t_line *res);
t_line		*gen_2d_map(char ***cor);

#endif

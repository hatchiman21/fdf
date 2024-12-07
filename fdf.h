/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:46 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/07 07:13:08 by aatieh           ###   ########.fr       */
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

typedef struct	s_var
{
	void	*mlx;
	void	*win;
	char	***cor;
	t_line	*res;
	t_data	img;
	int		width;
	int		height;
}				t_var;

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

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		drawline(t_line *res, t_height height, t_data *img);
int			close_win(int keycode, t_var *var);
int			close_exit(t_var *var);
t_line		*free_lines(t_line *lines);
char		***free_cor(char ***string);
void		free_all(t_var *var, char ***cor);
char		***grap_input(char *arg, int fd);
void		get_offset(t_line *lst, int *offset);
int			get_dest(int x, int y, int z, int is_x);
float		get_scale(t_line *lst, t_var *var);
t_height	min_max_height(t_line *res);
void		shift(t_line *res, t_var vars);
t_line		*plot(char ***cor, t_data *img);

#endif

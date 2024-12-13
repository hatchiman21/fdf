/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:21:52 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 15:49:11 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// static void	parse_column(int fd, t_var *vars, char **tab, int i)
// {
// 	t_point	*point;
// 	int		x_offset;
// 	int		y_offset;
// 	int		j;

// 	j = -1;
// 	while (++j < vars->cols)
// 	{
// 		if (!ft_isdigit(*tab[j]) && *tab[j] != '-')
// 			error_map(fd, vars, INVALID_MAP);
// 		point = &(vars->map_3d[i][j]);
// 		x_offset = (vars->cols - 1) * vars->interval / 2;
// 		y_offset = (vars->rows - 1) * vars->interval / 2;
// 		point->x = (double)j * (vars-> ) - x_offset;
// 		point->y = (double)i * (vars->interval) - y_offset;
// 		point->z = (double)ft_atoi(tab[j]) * (vars->interval);
// 		vars->high = ft_max(vars->high, point->z);
// 		vars->low = ft_min(vars->low, point->z);
// 		point->mapcolor = parse_color(fd, vars, tab[j]);
// 	}
// }

// void	parse_map(int fd, t_var *vars)
// {
// 	char	*line;
// 	char	*temp;
// 	char	**tab;
// 	int		i;

// 	i = -1;
// 	while (++i < vars->rows)
// 	{
// 		temp = get_next_line(fd);
// 		if (!temp)
// 			error_map(fd, vars, MALLOC);
// 		line = ft_strtrim(temp, "\n");
// 		free(temp);
// 		if (!line)
// 			error_map(fd, vars, MALLOC);
// 		tab = ft_split(line, ' ');
// 		free(line);
// 		if (!tab)
// 			error_map(fd, vars, MALLOC);
// 		parse_column(fd, vars, tab, i);
// 		ft_free_tab((void **)tab, vars->cols);
// 	}
// }

// static int	get_cols(int fd, t_var *vars, char *line)
// {
// 	char	**tab;
// 	char	*temp;
// 	int		i;

// 	temp = ft_strtrim(line, "\n");
// 	free(line);
// 	if (!temp)
// 		error_map(fd, vars, MALLOC);
// 	tab = ft_split(temp, ' ');
// 	free(temp);
// 	if (!tab)
// 		error_map(fd, vars, MALLOC);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		vars->high = ft_max(vars->high, ft_atoi(tab[i]));
// 		vars->low = ft_min(vars->low, ft_atoi(tab[i]));
// 		i++;
// 	}
// 	ft_free_tab((void **)tab, i);
// 	return (i);
// }

// void	get_dimensions(int fd, t_var *vars)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	if (!line)
// 		error_map(fd, vars, MALLOC);
// 	vars->cols = get_cols(fd, vars, line);
// 	if (vars->cols == 0)
// 		error_map(fd, vars, INVALID_MAP);
// 	vars->rows = 1;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		vars->rows++;
// 		if (vars->cols != get_cols(fd, vars, line))
// 			error_map(fd, vars, INVALID_MAP);
// 	}
// }

// static void	malloc_grid(t_var *vars)
// {
// 	int	i;

// 	vars->map_3d = malloc(sizeof(t_point *) * vars->rows);
// 	vars->map_2d = malloc(sizeof(t_point *) * vars->rows);
// 	if (!(vars->map_2d) || !(vars->map_3d))
// 	{
// 		free_map(vars);
// 		handle_error(MALLOC);
// 	}
// 	i = -1;
// 	while (++i < vars->rows)
// 	{
// 		vars->map_3d[i] = malloc(sizeof(t_point) * vars->cols);
// 		vars->map_2d[i] = malloc(sizeof(t_point) * vars->cols);
// 		if (!(vars->map_2d[i]) || !(vars->map_3d[i]))
// 		{
// 			if (i + 1 < vars->rows)
// 			{
// 				vars->map_3d[i + 1] = NULL;
// 				vars->map_2d[i + 1] = NULL;
// 			}
// 			free_map(vars);
// 			handle_error(MALLOC);
// 		}
// 	}
// }

// static t_var	*parse_input(char *filename)
// {
// 	int		fd;
// 	t_var	*vars;

// 	fd = open(filename, O_RDONLY, 0777);
// 	if (fd == -1)
// 		return (NULL);
// 	vars = malloc(sizeof(t_var));
// 	if (!vars)
// 	{
// 		close(fd);
// 		handle_error(MALLOC);
// 	}
// 	get_dimensions(fd, vars);
// 	close(fd);
// 	malloc_grid(vars);
// 	vars->interval = ft_min(WIDTH / vars->cols, HEIGHT / vars->rows) / 2;
// 	vars->interval = ft_max(2, vars->interval);
// 	fd = open(filename, O_RDONLY, 0777);
// 	parse_map(fd, vars);
// 	close(fd);
// 	set_zcolor(vars);
// 	return (vars);
// }

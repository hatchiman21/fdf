/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grap_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:34:55 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/25 23:28:08 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	***intial_malloc(int fd)
{
	char	***cor;
	char	*line;
	int		i;

	if (fd == -1)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	cor = malloc((i + 1) * sizeof(char **));
	return (cor);
}

void	count_cols_row(t_var *var)
{
	int	i;
	int	j;

	i = 0;
	while (var->cor && var->cor[i])
		i++;
	j = 0;
	while (var->cor && var->cor[0] && var->cor[0][j])
		j++;
	var->rows = i;
	var->cols = j;
}

void	grap_3d_map(t_var *var)
{
	int		i;
	int		j;

	count_cols_row(var);
	var->grid_3d = malloc(var->rows * sizeof(int *));
	if (!var->grid_3d)
		return ;
	i = 0;
	while (i < var->rows)
	{
		var->grid_3d[i] = malloc(var->cols * sizeof(int));
		if (!var->grid_3d[i])
		{
			free_3d_map(var->grid_3d, i);
			free(var->grid_3d);
			return ;
		}
		j = 0;
		while (j < var->cols)
		{
			var->grid_3d[i][j] = ft_atoi(var->cor[i][j]);
			j++;
		}
		i++;
	}
}

int	grap_file(char *arg, t_var *var)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(arg, O_RDONLY);
	var->cor = intial_malloc(fd);
	close(fd);
	if (!var->cor)
		return (-1);
	fd = open(arg, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		var->cor[i] = ft_split(line, ' ');
		if (!var->cor[i])
			return (-1);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	var->cor[i] = NULL;
	close(fd);
	return (0);
}

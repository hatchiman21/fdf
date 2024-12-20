/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:31:30 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/20 14:53:48 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	***free_cor(char ***string)
{
	int	i;
	int	j;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i])
	{
		j = 0;
		while (string[i][j])
			free(string[i][j++]);
		free(string[i++]);
	}
	free (string);
	return (NULL);
}

void	free_3d_map(int **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_2d_grid(t_point **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}

int	free_all(t_var *var)
{
	if (var->second)
	{
		if (var->second->on_display && var->second->img.img)
			mlx_destroy_image(var->mlx_win->mlx, var->second->img.img);
		free_2d_grid(var->second->grid_2d, var->second->rows);
		free(var->second);
	}
	if (var->mlx_win)
	{
		if (var->on_display && var->img.img)
			mlx_destroy_image(var->mlx_win->mlx, var->img.img);
		if (var->mlx_win && var->mlx_win->win)
			mlx_destroy_window(var->mlx_win->mlx, var->mlx_win->win);
		if (var->mlx_win && var->mlx_win->mlx)
		{
			mlx_destroy_display(var->mlx_win->mlx);
			free(var->mlx_win->mlx);
		}
		free(var->mlx_win);
	}
	if (var->grid_2d)
		free_2d_grid(var->grid_2d, var->rows);
	if (var->grid_3d)
		free_3d_map(var->grid_3d, var->rows);
	exit(0);
}

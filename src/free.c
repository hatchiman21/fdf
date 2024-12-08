/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:31:30 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 03:02:02 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	***free_map(char ***string)
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

void	free_points(t_point *point)
{
	t_point	*tmp;
	t_point	*tmp2;

	if (!point)
		return ;
	tmp = point->next_y;
	while (point)
	{
		tmp2 = point->next_x;
		free(point);
		if (tmp2)
			point = tmp2;
		else
		{
			point = tmp;
			if (tmp)
				tmp = tmp->next_y;
		}
	}
}

void	free_all(t_var *var, char ***map)
{
	if (var->mlx)
	{
		if (var->img.img)
			mlx_destroy_image(var->mlx, var->img.img);
		if (var->win)
			mlx_destroy_window(var->mlx, var->win);
		mlx_destroy_display(var->mlx);
		free(var->mlx);
	}
	free_points(var->point);
	free_map(map);
}

int	close_exit(t_var *var)
{
	mlx_destroy_image(var->mlx, var->img.img);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free_points(var->point);
	free_map(var->map);
	free(var->mlx);
	exit(0);
	return (0);
}

int	close_win(int keycode, t_var *var)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(var->mlx, var->img.img);
		mlx_destroy_window(var->mlx, var->win);
		mlx_destroy_display(var->mlx);
		free_points(var->point);
		free_map(var->map);
		free(var->mlx);
		exit(0);
	}
	return (0);
}

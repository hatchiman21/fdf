/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:31:30 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/09 20:28:41 by aatieh           ###   ########.fr       */
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

t_line	*free_lines(t_line *lines)
{
	t_line	*tmp;

	while (lines)
	{
		tmp = lines->next;
		free(lines);
		lines = tmp;
	}
	return (NULL);
}

void	free_all(t_var *var)
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
	free_lines(var->d2_line);
	free_cor(var->cor);
}

int	close_exit(t_var *var)
{
	mlx_destroy_image(var->mlx, var->img.img);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free_lines(var->d2_line);
	free_cor(var->cor);
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
		free_lines(var->d2_line);
		free_cor(var->cor);
		free(var->mlx);
		exit(0);
	}
	return (0);
}

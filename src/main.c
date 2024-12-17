/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:08:05 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/17 16:12:50 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	apply_zoom_to_lines(t_line *lst, float scale)
{
	while (lst)
	{
		lst->x0 = (int)round(scale * lst->x0);
		lst->y0 = (int)round(scale * lst->y0);
		lst->x1 = (int)round(scale * lst->x1);
		lst->y1 = (int)round(scale * lst->y1);
		lst = lst->next;
	}
}

int	handle_arguments(int argc, char *argv[], int *fd)
{
	if (argc != 2)
		return (ft_dprintf(2, "Wrong number of inputs\n"), 1);
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
	{
		ft_dprintf(2, "Error opening %s\n", argv[1]);
		return (2);
	}
	return (0);
}

int	initialize_variables(t_var *var, char *filename, int fd)
{
	var->cor = grap_map(filename, fd);
	close(fd);
	if (!var->cor)
		return (ft_dprintf(2, "Malloc failed\n"), 3);
	var->d2_line = gen_2d_map(var->cor);
	if (!var->d2_line)
	{
		ft_dprintf(2, "Malloc failed\n");
		free_cor(var->cor);
		return (3);
	}
	offset_map(var->d2_line);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_var	var;
	int		ret;

	ret = handle_arguments(argc, argv, &fd);
	if (ret != 0)
		return (ret);
	ret = initialize_variables(&var, argv[1], fd);
	if (ret != 0)
		return (ret);
	initialize_and_draw(&var);
	return (0);
}

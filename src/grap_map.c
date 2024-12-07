/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intiate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:34:55 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 00:50:09 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	***intial_malloc(int fd)
{
	char	***cor;
	char	*line;
	int		i;

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

char	***grap_map(char *arg, int fd)
{
	int		i;
	char	***cor;
	char	*line;

	cor = intial_malloc(fd);
	if (!cor)
		return (NULL);
	close(fd);
	fd = open(arg, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		cor[i] = ft_split(line, ' ');
		if (!cor[i])
			return (free_cor(cor));
		i++;
		free(line);
		line = get_next_line(fd);
	}
	cor[i] = NULL;
	return (cor);
}

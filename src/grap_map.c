/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grap_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:34:55 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/08 02:52:55 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	***intial_malloc(int fd)
{
	char	***map;
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
	map = malloc((i + 1) * sizeof(char **));
	return (map);
}

char	***grap_map(char *arg, int fd)
{
	int		i;
	char	***map;
	char	*line;

	map = intial_malloc(fd);
	if (!map)
		return (NULL);
	close(fd);
	fd = open(arg, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = ft_split(line, ' ');
		if (!map[i])
			return (free_map(map));
		i++;
		free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

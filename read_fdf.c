/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:11:53 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/15 20:06:26 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_col(t_map *map, int i, int start_j)
{
	while (start_j < map->col)
	{
		map->points[i][start_j].x = start_j;
		map->points[i][start_j].y = i;
		map->points[i][start_j].z = 0;
		map->points[i][start_j].color = 0xFFFFFF;
		start_j++;
	}
}

void	full_map_line(t_map *map, int i, char **number)
{
	int		j;
	char	**split;

	j = 0;
	while (j < map->col)
	{
		if (!number || !number[j])
			break ;
		split = ft_split(number[j], ',');
		if (!split)
			break ;
		map->points[i][j].x = j;
		map->points[i][j].y = i;
		map->points[i][j].z = ft_atoi(split[0]);
		map->points[i][j].color = parse_color(split[1]);
		free_number(split);
		j++;
	}
	fill_col(map, i, j);
}

int	alloc_points(t_map *map)
{
	int	i;

	map->points = malloc(sizeof(t_point *) * map->line);
	if (!map->points)
		return (0);
	i = 0;
	while (i < map->line)
	{
		map->points[i] = malloc(sizeof(t_point) * map->col);
		if (!map->points[i])
		{
			while (--i >= 0)
				free(map->points[i]);
			free(map->points);
			map->points = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

void	process_line(t_map *map, int i, char *line)
{
	char	**number;

	number = ft_split(line, ' ');
	if (number)
	{
		full_map_line(map, i, number);
		free_number(number);
	}
	else
		fill_col(map, i, 0);
	free(line);
}

void	full_map(t_map *map, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	i = 0;
	while (i < map->line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line(map, i, line);
		i++;
	}
	while (i < map->line)
		fill_col(map, i++, 0);
	close(fd);
}

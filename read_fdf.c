/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:11:53 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:42:21 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void full_map2(t_map *map, int i, char **number)
{
    int j;
    char **split;

    j = 0;
    while (j < map->col && number[j])
    {
        split = ft_split(number[j], ',');
        map->points[i][j].x = j;
        map->points[i][j].y = i;
        map->points[i][j].z = ft_atoi(split[0]);
        if (split[1])
            map->points[i][j].color = ft_atoi_base(split[1] + 2, 16);
        else
            map->points[i][j].color = 0xFFFFFF;
        free_number(split);
        j++;
    }
}


void free_number(char **number)
{
	int i;

	i = 0;
	if (!number)
		return ;
	while (number[i])
	{
		free(number[i]);
		i++;
	}
	free(number);
}
void full_map(t_map *map, char *file)
{
    int fd;
    int i;
    char *line;
    char **number;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return ;
    i = 0;
    while (i < map->line)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        number = ft_split(line, ' ');
        if (number)
        {
            full_map2(map, i, number);
            free_number(number);
        }
        free(line);
        i++;
    }
    close(fd);
}

int alloc_points(t_map *map)
{
    int i;

    map->points = malloc(sizeof(t_point *) * map->line);
    if (!map->points)
        return 0;
    i = 0;
    while (i < map->line)
    {
        map->points[i] = malloc(sizeof(t_point) * map->col);
        if (!map->points[i])
        {
            i--;
            while (i >= 0)
            {
                free(map->points[i]);
                i--;
            }
            free(map->points);
            return 0;
        }
        i++;
    }
    return 1;
}

t_map	*init_map(char *file, t_map *map)
{
	if (!alloc_points(map))
	{
		free(map);
		return (NULL);
	}
	full_map(map, file);
	return (map);
}

t_map *read_fdf(char *file)
{
	char *line;
	t_map *map;
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return(close(fd),NULL);
	map->col = 0;
	map->line = 0;
	map->points = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (map->line == 0)
			map->col = count_word(line,' ');
		map->line++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (init_map(file, map));
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:18 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/15 20:48:09 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*read_fdf(char *file)
{
	char	*line;
	t_map	*map;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (close(fd), NULL);
	map->col = 0;
	map->line = 0;
	map->points = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (map->line == 0)
			map->col = count_word(line, ' ');
		map->line++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (init_map(file, map));
}

void	init_mlx_and_draw(t_map *map)
{
	t_data	d;

	d.map = map;
	d.win_width = 1920;
	d.win_height = 1080;
	d.scale = 1.0f;
	d.z_scale = 1.0f;
	d.offset_x = 0.0f;
	d.offset_y = 0.0f;
	d.z_min = 0;
	d.z_max = 0;
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, d.win_width, d.win_height, "FDF");
	d.img = mlx_new_image(d.mlx, d.win_width, d.win_height);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line_len, &d.endian);
	compute_scale_offset(&d);
	d.scale *= 0.6;
	d.offset_x -= 380;
	d.offset_y -= 100;
	compute_z_range(&d);
	draw_map_lines(&d);
	mlx_put_image_to_window(d.mlx, d.win, d.img, 0, 0);
	mlx_key_hook(d.win, on_key, &d);
	mlx_hook(d.win, 17, 0, on_close, &d);
	mlx_loop(d.mlx);
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

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		return (1);
	map = read_fdf(argv[1]);
	if (!map)
		return (1);
	init_mlx_and_draw(map);
	free_map(map);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:18 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/14 14:25:28 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mlx_and_draw(t_map *map)
{
	t_data	d;

	d.map = map;
	d.win_width = 1920;
	d.win_height = 1080;
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, d.win_width, d.win_height, "FDF");
	d.img = mlx_new_image(d.mlx, d.win_width, d.win_height);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line_len, &d.endian);
	compute_scale_offset(&d);
	d.scale *= 0.7;
	d.offset_x += 275;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minilbx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:40 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/12 16:54:25 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mlx(t_data *data, int col, int ligne)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, col, ligne, "FDF");
	data->img = mlx_new_image(data->mlx, col, ligne);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
}

void	draw(t_data *data, int x, int y, int color)
{
	char	*draw;

	draw = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)draw = color;
}
t_coord project_iso(int x, int y, int z)
{
	t_coord p;
	float angle;

	angle = 0.523599;

	p.x = (x - y) * cos(angle);
	p.y = (x + y) * sin(angle) - z;

	return (p);
}

void init_mlx_and_draw(t_map *map)
{
	t_data data;
	t_coord coord;
	t_point point3d;
	int i;
	int j;

	i = 0;
	init_mlx(&data,  800, 600);
	while (i < map->line)
	{
		j = 0;
		while (j < map->col)
		{
			point3d = map->points[i][j];
			coord = project_iso(point3d.x,point3d.y ,point3d.z);
			draw(&data,coord.x,coord.y,0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data.mlx,data.win,data.img,0,0);
	mlx_loop(data.mlx);
}
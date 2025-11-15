/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:52:47 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/14 14:24:41 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *d, t_coord a, t_coord b, int color)
{
	t_line	l;

	l.dx = fabs(b.x - a.x);
	l.dy = fabs(b.y - a.y);
	if (l.dx > l.dy)
		l.steps = l.dx;
	else
		l.steps = l.dy;
	l.x_inc = (b.x - a.x) / l.steps;
	l.y_inc = (b.y - a.y) / l.steps;
	l.x = a.x;
	l.y = a.y;
	l.i = 0;
	while (l.i <= l.steps)
	{
		put_pixel(d, (int)l.x, (int)l.y, color);
		l.x += l.x_inc;
		l.y += l.y_inc;
		l.i++;
	}
}

void	draw_horizontal(t_data *d, int i, int j)
{
	t_coord	p1;
	t_coord	p2;
	int		color;

	if (j + 1 >= d->map->col)
		return ;
	p1 = priso(d->map->points[i][j], d);
	p2 = priso(d->map->points[i][j + 1], d);
	color = get_color(d->map->points[i][j]);
	draw_line(d, p1, p2, color);
}

void	draw_vertical(t_data *d, int i, int j)
{
	t_coord	p1;
	t_coord	p2;
	int		color;

	if (i + 1 >= d->map->line)
		return ;
	p1 = priso(d->map->points[i][j], d);
	p2 = priso(d->map->points[i + 1][j], d);
	color = get_color(d->map->points[i][j]);
	draw_line(d, p1, p2, color);
}

void	draw_map_lines(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (i < d->map->line)
	{
		j = 0;
		while (j < d->map->col)
		{
			draw_horizontal(d, i, j);
			draw_vertical(d, i, j);
			j++;
		}
		i++;
	}
}

t_coord	priso(t_point p, t_data *d)
{
	t_coord	result;
	float	angle;
	float	x;
	float	y;
	float	z;

	angle = -0.488692;
	x = p.x * d->scale;
	y = p.y * d->scale;
	z = p.z * d->z_scale * d->scale;
	result.x = (x + y) * cosf(angle) + d->offset_x;
	result.y = (x - y) * sinf(angle) - z + d->offset_y;
	return (result);
}

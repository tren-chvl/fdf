/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minilbx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:54:28 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/14 14:11:32 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	priso_base(t_point p, t_data *d)
{
	t_coord	result;
	float	angle;
	float	x;
	float	y;
	float	z;

	angle = -0.488692f;
	x = p.x;
	y = p.y;
	z = p.z * d->z_scale;
	result.x = (x + y) * cosf(angle);
	result.y = (x - y) * sinf(angle) - z;
	return (result);
}

void	compute_z_range(t_data *d)
{
	int	i;
	int	j;

	d->z_min = 1000000;
	d->z_max = -1000000;
	i = 0;
	while (i < d->map->line)
	{
		j = 0;
		while (j < d->map->col)
		{
			if (d->map->points[i][j].z < d->z_min)
				d->z_min = d->map->points[i][j].z;
			if (d->map->points[i][j].z > d->z_max)
				d->z_max = d->map->points[i][j].z;
			j++;
		}
		i++;
	}
	d->z_scale = 0.25;
}

void	init_bounds(t_minmax *b)
{
	b->min_x = 1e9;
	b->max_x = -1e9;
	b->min_y = 1e9;
	b->max_y = -1e9;
}

void	update_bounds(t_minmax *b, t_coord tmp)
{
	if (tmp.x < b->min_x)
		b->min_x = tmp.x;
	if (tmp.x > b->max_x)
		b->max_x = tmp.x;
	if (tmp.y < b->min_y)
		b->min_y = tmp.y;
	if (tmp.y > b->max_y)
		b->max_y = tmp.y;
}

void	compute_scale_offset(t_data *d)
{
	int			i;
	int			j;
	t_coord		tmp;
	t_minmax	b;

	init_bounds(&b);
	i = 0;
	while (i < d->map->line)
	{
		j = 0;
		while (j < d->map->col)
		{
			tmp = priso_base(d->map->points[i][j], d);
			update_bounds(&b, tmp);
			j++;
		}
		i++;
	}
	d->scale = fmin((d->win_width - 40) / (b.max_x - b.min_x),
			(d->win_height - 40) / (b.max_y - b.min_y));
	d->offset_x = (d->win_width - (b.max_x - b.min_x) * d->scale)
		/ 2 - b.min_x * d->scale - 20;
	d->offset_y = (d->win_height - (b.max_y - b.min_y) * d->scale)
		/ 2 - b.min_y * d->scale;
}

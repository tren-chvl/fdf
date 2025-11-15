/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minilbx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:54:28 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/15 21:03:27 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	compute_scale_offset(t_data *d)
{
	float	scale_x;
	float	scale_y;

	scale_x = (float)d->win_width / (float)(d->map->col + 1);
	scale_y = (float)d->win_height / (float)(d->map->line + 1);
	if (scale_x < scale_y)
		d->scale = scale_x;
	else
		d->scale = scale_y;
	d->scale *= 0.9f;
	d->offset_x = d->win_width / 2;
	d->offset_y = d->win_height / 2;
}

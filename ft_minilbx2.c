/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minilbx2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:53:13 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/14 12:38:06 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= d->win_width || y < 0 || y >= d->win_height)
		return ;
	dst = d->addr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_point p)
{
	return (p.color);
}

void	destroy_and_quit(t_data *d, int code)
{
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
		mlx_destroy_display(d->mlx);
	if (d->mlx)
		free(d->mlx);
	if (d->map)
		free_map(d->map);
	exit(code);
}

int	on_key(int key, t_data *d)
{
	if (key == 65307)
		destroy_and_quit(d, 0);
	return (0);
}

int	on_close(t_data *d)
{
	destroy_and_quit(d, 0);
	return (0);
}

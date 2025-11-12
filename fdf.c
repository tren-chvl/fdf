/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:18 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/12 16:34:26 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
	t_map *map;

	if (argc != 2)
		return (1);
	map = read_fdf(argv[1]);
	if (!map)
		return (1);
	full_map(map,argv[1]);
	init_mlx_and_draw(map);
	free_map(map);
	return (0);
}


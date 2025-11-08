/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:18 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/08 23:11:38 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int main(void)
{
    void    *mlx;
    void    *win;

    mlx = mlx_init();
    if (!mlx)
        return (write(2, "Erreur init mlx\n", 17), 1);

    win = mlx_new_window(mlx, 800, 600, "FDF");
    if (!win)
        return (write(2, "Erreur creation fenetre\n", 25), 1);

    mlx_loop(mlx);
    return (0);
}
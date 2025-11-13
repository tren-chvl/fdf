// debug_visual.c
#include "fdf.h"
#include <stdio.h>
#include <math.h>

t_coord project_iso_debug(t_point p, int scale, int off_x, int off_y)
{
    t_coord result;
    float angle = 0.523599; // 30° en rad
    result.x = (p.x - p.y) * cos(angle) * scale + off_x;
    result.y = (p.x + p.y) * sin(angle) * scale - (p.z / 2.0) * scale + off_y;
    return result;
}

void put_pixel_debug(t_data *d, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= d->win_width || y < 0 || y >= d->win_height)
        return;
    dst = d->addr + (y * d->line_len + x * (d->bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_corner_square(t_data *d, t_coord p, int size, int color)
{
    for (int i = -size; i <= size; i++)
        for (int j = -size; j <= size; j++)
            put_pixel_debug(d, p.x + i, p.y + j, color);
}

void compute_scale_offset_debug(t_data *d, t_coord *corners)
{
    int i, j;
    t_coord tmp;
    float min_x = 1e9, max_x = -1e9;
    float min_y = 1e9, max_y = -1e9;

    for (i = 0; i < d->map->line; i++)
    {
        for (j = 0; j < d->map->col; j++)
        {
            tmp = project_iso_debug(d->map->points[i][j], 1, 0, 0);
            if (tmp.x < min_x) min_x = tmp.x;
            if (tmp.x > max_x) max_x = tmp.x;
            if (tmp.y < min_y) min_y = tmp.y;
            if (tmp.y > max_y) max_y = tmp.y;
        }
    }

    float map_width = max_x - min_x;
    float map_height = max_y - min_y;

    float scale_x = (d->win_width - 40) / map_width;
    float scale_y = (d->win_height - 40) / map_height;
    d->scale = fmin(scale_x, scale_y);

    d->offset_x = d->win_width / 2 - ((min_x + max_x) / 2.0) * d->scale;
    d->offset_y = d->win_height / 2 - ((min_y + max_y) / 2.0) * d->scale;

    // Mettre les 4 coins projetés dans corners pour visualiser
    corners[0] = project_iso_debug((t_point){0,0,0,0}, d->scale, d->offset_x, d->offset_y);
    corners[1] = project_iso_debug((t_point){d->map->col-1,0,0,0}, d->scale, d->offset_x, d->offset_y);
    corners[2] = project_iso_debug((t_point){0,d->map->line-1,0,0}, d->scale, d->offset_x, d->offset_y);
    corners[3] = project_iso_debug((t_point){d->map->col-1,d->map->line-1,0,0}, d->scale, d->offset_x, d->offset_y);

    // 🔹 Debug print
    printf("DEBUG: map_width=%.2f map_height=%.2f\n", map_width, map_height);
    printf("DEBUG: scale_x=%.2f scale_y=%.2f -> scale=%.2f\n", scale_x, scale_y, (double)d->scale);
    printf("DEBUG: min_x=%.2f max_x=%.2f min_y=%.2f max_y=%.2f\n", min_x, max_x, min_y, max_y);
    printf("DEBUG: offset_x=%.2f offset_y=%.2f\n", (double)d->offset_x, (double)d->offset_y);
}

void init_mlx_and_draw_debug(t_map *map)
{
    t_data d;
    t_coord corners[4];

    d.map = map;
    d.win_width = 1200;
    d.win_height = 800;

    d.mlx = mlx_init();
    if (!d.mlx) return;

    d.win = mlx_new_window(d.mlx, d.win_width, d.win_height, "FDF DEBUG VISUAL");
    d.img = mlx_new_image(d.mlx, d.win_width, d.win_height);
    d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line_len, &d.endian);

    compute_scale_offset_debug(&d, corners);  // calcule scale/offset et coins
    draw_map_lines(&d);                        // dessine toutes les lignes

    // Dessine un petit carré rouge sur les 4 coins du parallélogramme
    for (int k = 0; k < 4; k++)
        draw_corner_square(&d, corners[k], 5, 0xFF0000);

    mlx_put_image_to_window(d.mlx, d.win, d.img, 0, 0);
    mlx_loop(d.mlx);
}

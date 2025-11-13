#include "fdf.h"

void put_pixel(t_data *d, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= d->win_width || y < 0 || y >= d->win_height)
        return ;
    dst = d->addr + (y * d->line_len + x * (d->bpp / 8));
    *(unsigned int *)dst = color;
}

int get_color(t_point p)
{
    return (p.color);
}

t_coord project_iso(t_point p, t_data *d, float scale, float off_x, float off_y)
{
    t_coord result;
    float   angle;
    float   x;
    float   y;
    float   z;

    angle = -0.488692;
    x = p.x * scale;
    y = p.y * scale;
    z = p.z * d->z_scale * scale;
    result.x = (x + y) * cos(angle) + off_x;
    result.y = (x - y) * sin(angle) - z + off_y;

    return (result);
}


void update_minmax(t_coord tmp, float *min_x, float *max_x,
        float *min_y, float *max_y)
{
    if (tmp.x < *min_x)
        *min_x = tmp.x;
    if (tmp.x > *max_x)
        *max_x = tmp.x;
    if (tmp.y < *min_y)
        *min_y = tmp.y;
    if (tmp.y > *max_y)
        *max_y = tmp.y;
}
void    compute_scale_offset(t_data *d)
{
    int     i;
    int     j;
    t_coord tmp;
    float   min_x;
    float   max_x;
    float   min_y;
    float   max_y;

    min_x = 1e9;
    max_x = -1e9;
    min_y = 1e9;
    max_y = -1e9;
    i = 0;
    while (i < d->map->line)
    {
        j = 0;
        while (j < d->map->col)
        {
            tmp = project_iso(d->map->points[i][j], d, 1, 0, 0);
            if (tmp.x < min_x) min_x = tmp.x;
            if (tmp.x > max_x) max_x = tmp.x;
            if (tmp.y < min_y) min_y = tmp.y;
            if (tmp.y > max_y) max_y = tmp.y;
            j++;
        }
        i++;
    }
    d->scale = fmin((d->win_width - 40) / (max_x - min_x),
            (d->win_height - 40) / (max_y - min_y));
    d->offset_x = (d->win_width - (max_x - min_x) * d->scale) / 2 - min_x * d->scale;
    d->offset_y = (d->win_height - (max_y - min_y) * d->scale) / 2 - min_y * d->scale;

    d->offset_x -= 20; 
    
}



void    compute_z_range(t_data *d)
{
    int i;
    int j;

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
    d->z_scale = 0.2;
}



#include "fdf.h"

void destroy_and_quit(t_data *d, int code)
{
    if (d->img)
        mlx_destroy_image(d->mlx, d->img);
    if (d->win)
        mlx_destroy_window(d->mlx, d->win);
# ifndef __APPLE__
    if (d->mlx)
        mlx_destroy_display(d->mlx);
# endif
    if (d->mlx)
        free(d->mlx);
    if (d->map)
        free_map(d->map);
    exit(code);
}

int on_key(int key, t_data *d)
{
    if (key == 65307 || key == 53) // ESC Linux/Mac
        destroy_and_quit(d, 0);
    return (0);
}

int on_close(t_data *d)
{
    destroy_and_quit(d, 0);
    return (0);
}

void    init_mlx_and_draw(t_map *map)
{
    t_data  d;

    d.map = map;
    d.win_width = 1200;
    d.win_height = 800;
    d.mlx = mlx_init();
    d.win = mlx_new_window(d.mlx, d.win_width, d.win_height, "FDF");
    d.img = mlx_new_image(d.mlx, d.win_width, d.win_height);
    d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line_len, &d.endian);
    compute_scale_offset(&d);
    compute_z_range(&d);
    draw_map_lines(&d);
    mlx_put_image_to_window(d.mlx, d.win, d.img, 0, 0);
    mlx_key_hook(d.win, on_key, &d);
    mlx_hook(d.win, 17, 0, on_close, &d);
    mlx_loop(d.mlx);
}

// void	init_mlx_and_draw(t_map *map)
// {
// 	t_data	d;

// 	d.map = map;
// 	d.win_width = 1200;
// 	d.win_height = 800;
// 	d.mlx = mlx_init();
// 	d.win = mlx_new_window(d.mlx, d.win_width, d.win_height, "FDF");
// 	d.img = mlx_new_image(d.mlx, d.win_width, d.win_height);
// 	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line_len, &d.endian);
// 	compute_scale_offset(&d);
// 	compute_z_range(&d);
// 	draw_map_lines(&d);
// 	mlx_put_image_to_window(d.mlx, d.win, d.img, 0, 0);
// 	mlx_loop(d.mlx);
// }

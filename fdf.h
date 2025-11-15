/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:39:39 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/15 21:03:14 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <math.h>
# include "minilibx-linux/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_minmax
{
	float	min_y;
	float	min_x;
	float	max_x;
	float	max_y;
}	t_minmax;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	t_point	**points;
	int		line;
	int		col;
}	t_map;

typedef struct s_coord
{
	float	x;
	float	y;
}	t_coord;

typedef struct s_line
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	x_inc;
	float	y_inc;
	int		steps;
	int		i;
}	t_line;

typedef struct s_data
{
	t_map	*map;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		win_width;
	int		win_height;
	float	scale;
	float	z_scale;
	float	offset_x;
	float	offset_y;
	int		z_min;
	int		z_max;
}	t_data;

t_map	*read_fdf(char *file);
t_map	*init_map(char *file, t_map *map);
int		alloc_points(t_map *map);
void	full_map(t_map *map, char *file);
void	free_number(char **number);
void	free_map(t_map *map);
void	fill_col(t_map *map, int i, int start_j);
void	full_map_line(t_map *map, int i, char **number);
void	process_line(t_map *map, int i, char *line);

int		get_color(t_point p);
void	put_pixel(t_data *d, int x, int y, int color);
t_coord	priso(t_point p, t_data *d);
void	draw_line(t_data *data, t_coord a, t_coord b, int color);
void	draw_horizontal(t_data *d, int i, int j);
void	draw_vertical(t_data *d, int i, int j);
void	draw_map_lines(t_data *data);
void	compute_scale_offset(t_data *data);
void	compute_z_range(t_data *data);

void	destroy_and_quit(t_data *d, int code);
void	init_mlx_and_draw(t_map *map);
int		on_key(int key, t_data *d);
int		on_close(t_data *d);
int		parse_color(char *s);
void	free_number(char **number);

char	*get_next_line(int fd);
char	*read_newline(int fd, char *line);
char	*extract_line(char *line);
char	*clean_line(char *line);

size_t	ft_strlen_g(char *line);
char	**ft_split(char *s, char c);
int		count_word(char *s, char c);
int		ft_atoi(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*free_return(char *s1, char *join);
int		ft_atoi_base(const char *str, int base);

int		ft_printf(const char *str, ...);
int		ft_putnbr(int nb);
int		ft_putstr(char *s);
int		ft_put(unsigned int nb);
int		ft_convert(unsigned long str);
int		ft_hexa_unsigned(unsigned int nb, int uppercase);
int		ft_addr(void *ptr);
int		ft_pourcentage(char c, va_list args);
int		pourcentage_c(va_list args);
int		pourcentage_double(void);
int		pourcentage_int(va_list args);
int		pourcentage_s(va_list args);
int		pourcentage_addr(va_list args);
int		pourcentage_u(va_list args);
int		pourcentage_x(va_list args, int uppercase);

#endif

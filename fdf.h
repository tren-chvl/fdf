/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:40 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:25:10 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <math.h>
#include "minilibx-linux/mlx.h"

typedef struct s_point
{
	int x;
	int y;
	int z;
}   t_point;

typedef struct s_map
{
	t_point **points;
	int line;
	int col;
}   t_map;

typedef struct s_data
{
	t_map *map;
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
}	t_data;

typedef struct s_coord
{
	int x;
	int y;
}	t_coord;

char	*get_next_line(int fd);
char	*read_newline(int fd, char *line);
char	*extract_line(char *line);
char	*clean_line(char *line);

size_t	ft_strlen_g(char *line);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*free_return(char *s1, char *join);
int		count_word(char *s);
char	**ft_split(char *str);
int		ft_atoi(char *str);

int	ft_putnbr(int nb);
int	ft_convert(unsigned long str);
int	ft_addr(void *ptr);
int	ft_putstr(char *s);
int	ft_put(unsigned int nb);
int	ft_hexa_unsigned(unsigned int nb, int uppercase);
int	ft_pourcentage(char c, va_list args);
int	ft_printf(const char *str, ...);

int	pourcentage_c(va_list args);
int	pourcentage_double(void);
int	pourcentage_int(va_list args);
int	pourcentage_s(va_list args);
int	pourcentage_addr(va_list args);
int	pourcentage_u(va_list args);
int	pourcentage_x(va_list args, int uppercase);

t_map	*read_fdf(char *file);
int	alloc_points(t_map *map);
void free_map(t_map *map);
t_map	*init_map(char *file, t_map *map);
void	full_map(t_map *map, char *file);

#endif
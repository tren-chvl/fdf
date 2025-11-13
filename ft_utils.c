/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:16:42 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 11:22:11 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_atoi(char *str)
{
	int result;
	int signe;
	int i;

	i = 0;
	result = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			signe = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (signe * result);
}


void free_map(t_map *map)
{
    int i;

    if (!map)
        return ;
    i = 0;
    while (i < map->line)
    {
        if (map->points[i])
            free(map->points[i]);
        i++;
    }
    free(map->points);
    free(map);
}

int ft_atoi_base(const char *str, int base)
{
    int result = 0;
    int i = 0;
    char c;

    if (base < 2 || base > 16)
        return 0;
    while (str[i])
    {
        c = str[i];
        if (c >= '0' && c <= '9')
            c = c - '0';
        else if (c >= 'A' && c <= 'F')
            c = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            c = c - 'a' + 10;
        else
            break ;
        if (c >= base)
            break ;
        result = result * base + c;
        i++;
    }
    return result;
}
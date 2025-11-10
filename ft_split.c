/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:41:39 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 12:04:55 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void free_str(char **tab,int i)
{
	while (i--)
		free(tab[i]);
	free(tab);	
}
char *wordup(char *str)
{
	char *word;
	int len;
	int i;

	i = 0;
	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
int count_word(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		if (*str)
		{
			count++;
			while (*str && *str != ' ')
				str++;
		}
	}
	return (count);
}
int full_tab(char *str,char **tab)
{
	int i;

	i = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		if (*str)
		{
			tab[i++] = wordup(str);
			if (!tab[i])
			{
				free_str(tab,i);
				return (0);
			}
			while (*str && *str != ' ')
				str++;
		}
	}
	tab[i] = NULL;
	return (1);
}
char **ft_split(char *str)
{
	char **tab;
	int count;

	if (!str)
		return (NULL);
	count = count_word(str);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	if (!full_tab(str,tab))
		return (NULL);
	return (tab);
}
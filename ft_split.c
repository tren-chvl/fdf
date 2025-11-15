/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:51:33 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/14 09:51:35 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_stp(char **tab, int i)
{
	while (i--)
		free(tab[i]);
	free(tab);
}

int	count_word(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*word_dup(char *s, char c)
{
	size_t	i;
	size_t	len;
	char	*word;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	full_tab(char **tab, char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			tab[i] = word_dup(s, c);
			if (!tab[i])
			{
				free_stp(tab, i);
				return (0);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (1);
}

char	**ft_split(char *s, char c)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	if (!full_tab(tab, s, c))
		return (NULL);
	return (tab);
}

// int count_word(const char *s,char c)
// {
// 	int count;

// 	count = 0;
// 	while(*s)
// 	{
// 		while(*s == c)
// 			s++;
// 		if (*s)
// 		{
// 			count++;
// 			while (*s && *s != c)
// 				s++;
// 		}
// 	}
// 	return (count);
// }

// char *word_dup(char const *s,char c)
// {
// 	size_t i;
// 	size_t len;
// 	char *word;

// 	len = 0;
// 	i = 0;
// 	while (s[len] && s[len] != c)
// 		len++;
// 	word = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!word)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		word[i] = s[i];
// 		i++;
// 	}
// 	word[i] = '\0';
// 	return (word);	
// }

// char **ft_split(char const *s, char c)
// {
// 	int i;
// 	int count;
// 	char **tab;

// 	if (!s)
// 		return (NULL);
// 	count = count_word(s,c);
// 	tab = (char **)malloc(sizeof(char *) * (count + 1));
// 	i = 0;
// 	if (!tab)
// 		return(NULL);
// 	while (*s)
// 	{
// 		while ( *s && *s == c)
// 			s++;
// 		if (*s)
// 		{
// 			tab[i] = word_dup(s,c);
// 			i++;
// 			 while (*s && *s != c)
// 		 		s++;
// 		}
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }
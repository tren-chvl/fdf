#include "fdf.h"

int count_word(const char *s,char c)
{
	int count;

	count = 0;
	while(*s)
	{
		while(*s == c)
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

char *word_dup(char const *s,char c)
{
	size_t i;
	size_t len;
	char *word;

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

char **ft_split(char const *s, char c)
{
	int i;
	int count;
	char **tab;

	if (!s)
		return (NULL);
	count = count_word(s,c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!tab)
		return(NULL);
	while (*s)
	{
		while ( *s && *s == c)
			s++;
		if (*s)
		{
			tab[i] = word_dup(s,c);
			i++;
			 while (*s && *s != c)
		 		s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

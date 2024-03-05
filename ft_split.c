/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:14:25 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/03 15:56:37 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_cut(const char *str, char c)
{
	size_t	i;
	size_t	cmpt;

	i = 0;
	cmpt = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] && str[i + 1] && str[i] == c)
				i++;
			if (str[i] && str[i] != c)
				cmpt++;
		}
		i++;
	}
	if (str[0] != c && str[0])
		cmpt++;
	return (cmpt);
}

static int	ft_lengh_word(const char *str, char c)
{
	size_t	i;
	size_t	lengh;

	i = 0;
	lengh = 0;
	while (str[i] && str[i] != c)
	{
		lengh++;
		i++;
	}
	return (lengh);
}

static char	**ft_free( char **split)
{
	int		i;

	i = -1;
	if (split)
	{
		while (split[++i])
			free(split[i]);
		free(split);
	}
	return (NULL);
}

static char	**ft_fill(size_t i, char const *s, size_t cut, char c)
{
	char	**tab;
	size_t	j;
	size_t	string;

	j = 0;
	string = 0;
	tab = malloc(sizeof(char *) * (cut + 1));
	if (!tab)
		return (NULL);
	while (cut > j)
	{
		string = 0;
		tab[j] = malloc(sizeof(char) * (ft_lengh_word(&s[i], c) + 1));
		if (!tab[j])
			return (ft_free(tab));
		while (s[i] != c && s[i])
			tab[j][string++] = s[i++];
		tab[j][string] = '\0';
		j++;
		while (s[i] == c)
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	cut;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	if (!s[0])
	{
		tab = malloc(sizeof(char *));
		if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	while (s[i] == c)
		i++;
	cut = ft_cut(s, c);
	return (ft_fill(i, s, cut, c));
}

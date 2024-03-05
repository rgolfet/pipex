/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:16:33 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/03 15:56:27 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*cpy;
	size_t		i;

	if (!s1 && !s2)
		return (NULL);
	cpy = malloc((sizeof (char)) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		cpy[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	cpy[i + ft_strlen(s1)] = '\0';
	return (cpy);
}

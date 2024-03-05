/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:08:21 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/05 22:16:51 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	ft_free_arg(char **argument)
{
	size_t	i;

	i = 0;
	while (argument[i])
	{
		free(argument[i]);
		i++;
	}
}

int	ft_blank_command_error(char *argv, char *argv1)
{
	if (argv1[0] == '\0')
		ft_printf("permission denied :\n");
	if (argv[0] == '\0')
	{
		ft_printf("permission denied :\n");
		return (-1);
	}
	return (0);
}

int	ft_access(char *str)
{
	if (str == NULL)
		return (-1);
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) == 0)
			return (0);
		return (ft_printf("%s : permission denied", str), -1);
	}
	return (1);
}

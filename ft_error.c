/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:08:21 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/06 17:19:36 by rgolfett         ###   ########lyon.fr   */
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

void	ft_close3(int fd1, int fd2, int fd3)
{
	close(fd1);
	close(fd2);
	close(fd3);
}

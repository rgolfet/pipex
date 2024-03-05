/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:06:42 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/05 22:16:59 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int	ft_is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

char	*ft_find_cmd(const char *str)
{
	size_t		i;
	char		*res;

	i = 0;
	while (ft_is_white_space(str[i]) == 0 && str[i])
		i++;
	res = ft_strdup(str);
	if (!res)
		return (NULL);
	if (str[i])
		res[i] = '\0';
	return (res);
}

char	*ft_find_cmd_arg(char *str)
{
	size_t	j;

	j = 0;
	while (ft_is_white_space(str[j]) == 0 && str[j])
		j++;
	if (!str[j])
		return (NULL);
	return (&str[j]);
}

int	ft_count_args(char *cmd_arg)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	if (cmd_arg == NULL)
		return (0);
	while (ft_is_white_space (cmd_arg[i]) == 1 && cmd_arg[i])
		i++;
	if (!cmd_arg[i])
		return (0);
	while (cmd_arg[i])
	{
		while (ft_is_white_space(cmd_arg[i]) == 1 && cmd_arg[i])
			i++;
		if (cmd_arg[i])
		{
			while (ft_is_white_space(cmd_arg[i]) == 0 && cmd_arg[i])
				i++;
			cnt++;
		}
	}
	return (cnt);
}

char	*get_arg(char *cmd_arg, char **save_cmd_arg)
{
	size_t		i;
	size_t		j;
	char		*cpy;

	if (cmd_arg == NULL)
		return (NULL);
	j = 0;
	while (ft_is_white_space(cmd_arg[j]) == 1 && cmd_arg[j])
		j++;
	if (!cmd_arg[j])
		return (NULL);
	i = j;
	while (ft_is_white_space(cmd_arg[i]) == 0 && cmd_arg[i])
		i++;
	cpy = ft_strdup(&cmd_arg[j]);
	if (!cpy)
		return (NULL);
	cpy[i - j] = '\0';
	*save_cmd_arg = cmd_arg + i;
	return (cpy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:02:46 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/06 15:48:54 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

char	**ft_fill_av(char *path_cmd, char *cmd_arg)
{
	char	**argument;
	size_t	size;
	size_t	index;

	size = ft_count_args(cmd_arg);
	index = 1;
	argument = malloc (sizeof (char *) * (size + 2));
	if (!argument)
		return (NULL);
	argument[0] = path_cmd;
	while (index < (size + 1))
	{
		argument[index] = get_arg(cmd_arg, &cmd_arg);
		if (!argument[index])
			return (ft_free_arg(argument), NULL);
		index++;
	}
	argument[index] = NULL;
	return (argument);
}

char	*ft_find_path(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			if (!envp[i][4])
				return (envp[i] + 4);
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

char	*ft_create_path_command(char *path, char *cmd)
{
	char	*str;
	char	*cpy;

	str = ft_strjoin(path, "/");
	cpy = str;
	str = ft_strjoin(str, cmd);
	free (cpy);
	return (str);
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

char	*ft_path(char *path, char *cmd)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	j = 0;
	if (cmd[0] == '\0')
		return (NULL);
	if (ft_access(cmd) == 0)
		return (cmd);
	while (path[i])
	{
		while (path[i] && path[i] != ':')
			i++;
		if (path[i] == ':')
		{
			path[i] = '\0';
			str = ft_create_path_command(&path[j], cmd);
			if (ft_access(str) == -1)
				return (free(str), NULL);
			if (ft_access(str) == 0)
				return (str);
			free(str);
		}
		i++;
		j = i;
	}
	return (ft_printf("command not found : %s\n", cmd), NULL);
}

int	ft_child_1(char *infile, char *cmd, char **envp, int *pipe_fds)
{
	int		fd_in;
	char	*cmd_arg;
	char	*path_cmd;
	char	*path;
	char	**av;

	path = ft_find_path(envp);
	if (path == NULL)
		return (-1);
	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		return (ft_printf("no such file or directory: %s\n", infile), -1);
	cmd_arg = ft_find_cmd_arg(cmd);
	cmd = ft_find_cmd(cmd);
	path_cmd = ft_path(path, cmd);
	free(cmd);
	if (path_cmd == NULL)
		return (ft_close3(pipe_fds[1], pipe_fds[0], fd_in), -1);
	av = ft_fill_av(path_cmd, cmd_arg);
	dup2(fd_in, 0);
	dup2(pipe_fds[1], 1);
	ft_close3(pipe_fds[1], pipe_fds[0], fd_in);
	execve(av[0], av, envp);
	return (-1);
}

int	ft_child_2(char *outfile, char *cmd2, char **envp, int *pipe_fds)
{
	int		fd_out;
	char	*cmd_arg;
	char	*path_cmd;
	char	*path;
	char	**av;

	path = ft_find_path(envp);
	if (path == NULL)
		return (-1);
	fd_out = open(outfile, O_WRONLY | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1)
		return (ft_printf("permission denied: %s\n", outfile), -1);
	cmd_arg = ft_find_cmd_arg(cmd2);
	cmd2 = ft_find_cmd(cmd2);
	path_cmd = ft_path(path, cmd2);
	free(cmd2);
	if (path_cmd == NULL)
		return (ft_close3(pipe_fds[1], pipe_fds[0], fd_out), -1);
	av = ft_fill_av(path_cmd, cmd_arg);
	dup2(fd_out, 1);
	dup2(pipe_fds[0], 0);
	ft_close3(pipe_fds[1], pipe_fds[0], fd_out);
	execve(av[0], av, envp);
	return (-1);
}

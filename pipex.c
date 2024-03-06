/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:02:46 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/06 17:20:07 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

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

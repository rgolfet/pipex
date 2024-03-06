/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:03:24 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/06 14:35:03 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_find_path(char **envp);
int		main(int argc, char **argv, char **envp);
char	*ft_strdup(const char *s);
int		ft_is_white_space(char c);
char	*ft_find_cmd(const char *str);
char	*ft_find_cmd_arg(char *str);
int		ft_count_args(char *cmd_arg);
char	*get_arg(char *cmd_arg, char **save_cmd_arg);
void	ft_free_arg(char **argument);
int		ft_blank_command_error(char *argv, char *argv1);
char	**ft_fill_av(char *path_cmd, char *cmd_arg);
char	*ft_find_path(char **envp);
int		ft_access(char *str);
char	*ft_path(char *path, char *cmd);
int		ft_child_1(char *infile, char *cmd, char **envp, int *pipe_fds);
int		ft_child_2(char *outfile, char *cmd2, char **envp, int *pipe_fds);
void	ft_close3(int fd1, int fd2, int fd3);

#endif
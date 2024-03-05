/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:09:29 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/05 22:09:46 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int	main(int argc, char **argv, char **envp)
{
	int	tab[2];
	int	pid[2];

	if (argc != 5)
		return (-1);
	if (ft_blank_command_error(argv[2], argv[3]) == -1)
		return (-1);
	pipe(tab);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		if (ft_child_1(argv[1], argv[2], envp, tab) == -1)
			return (-1);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		if (ft_child_2(argv[4], argv[3], envp, tab) == -1)
			return (-1);
	}
	close(tab[0]);
	close(tab[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

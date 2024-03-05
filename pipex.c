
#include "pipex.h"
#include "ft_printf.h"

int	ft_is_white_space(char c)
{
	if ((c >=  9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

char *ft_find_cmd(const char *str)
{
	size_t	i;
	char *res;

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
		while (ft_is_white_space(cmd_arg[i]) == 0 && cmd_arg[i])
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

char *get_arg(char *cmd_arg, char **save_cmd_arg)
{
	size_t	i;
	size_t	j;
	char *cpy;

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
	return(cpy);
}

void	ft_free(char **argument)
{
	size_t	i;

	i = 0;
	while (argument[i])
	{
		free(argument[i]);
		i++;
	}
}

char **ft_fill_av(char *path_cmd, char *cmd_arg)
{
	char	**argument;
	size_t size;
	int start;
	int index;

	size = ft_count_args(cmd_arg);
	start = 0;
	index = 1;
	argument = malloc (sizeof (char *) * (size + 2));
	if (!argument)
		return (NULL);
	argument[0] = path_cmd;
	while (index < (size + 1))
	{
		argument[index] = get_arg(cmd_arg, &cmd_arg);
		if (!argument[index])
			return (ft_free(argument), NULL);
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

char *ft_path(char *path, char *cmd)
{
	size_t	i;
	size_t	j;
	char	*str;
	
	i = 0;
	j = 0;
	while (path[i])
	{
		while (path[i] && path[i] != ':')
			i++;
		if (path[i] == ':')
		{
			path[i] = '\0';
			str = ft_strjoin(&path[j], "/");
			str = ft_strjoin(str, cmd);
			if (str == NULL)
				return (NULL);
			if (access(str, F_OK) == 0)
			{
				if (access(str, X_OK) == 0)
					return (str);
				return (ft_printf("%s : permission denied", str), NULL);
			}
		}
		i++;
		j = i;
	}
	return (ft_printf("command not found : %s\n", cmd), NULL);
}

int main(int argc, char **argv, char **envp)
{
	int fd_in;
	int fd_out;
	int tab[2];
	char *path;
	char *cmd_arg;
	char *path_cmd;
	char *cmd;
	int pid[2];
	char **av;

	if (argc != 4)
		return (-1);
	path = ft_find_path(envp);
	if (path == NULL)
		return (-1);
	
	pipe(tab);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		fd_in = open(argv[1], O_RDONLY);
		if (fd_in == -1)
			return (ft_printf("no such file or directory: %s\n", argv[1]), -1);
		cmd = ft_find_cmd(argv[2]);
		cmd_arg = ft_find_cmd_arg(argv[2]);
		path_cmd = ft_path(path, cmd);
		av = ft_fill_av(path_cmd, cmd_arg);
		dup2(fd_in, 0);
		dup2(tab[1], 1);
		close(tab[0]);
		close(tab[1]);
		close(fd_in);
		execve(av[0], av, envp);
	}

	pid[1] = fork();
	if (pid[1] == 0)
	{
		fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd_out == -1)
			return(ft_printf("permission denied: %s\n", argv[4]));
		cmd = ft_find_cmd(argv[3]);
		cmd_arg = ft_find_cmd_arg(argv[3]);
		path_cmd = ft_path(path, cmd);
		av = ft_fill_av(path_cmd, cmd_arg);
		dup2(fd_out, 1);
		dup2(tab[0], 0);
		close(tab[1]);
		close(fd_out);
		close(tab[0]);
		execve(av[0], av, envp);
	}
	close(tab[0]);
	close(tab[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}

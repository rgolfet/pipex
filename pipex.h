#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
#include <sys/wait.h>


int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_find_path(char **envp);
char *ft_path(char *path, char *argm);
int main(int argc, char **argv, char **envp);
char	*ft_strdup(const char *s);

#endif
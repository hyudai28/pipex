#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./../libft/libft.h"

void	error_message(char *err_msg)
{
	printf("%s\n", err_msg);
	exit(1);
}

void    make_env_path(char ***path, char **envp)
{
    //envpからPATHの行を抜き出す
    int i;
    char *path_line;

    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4))
        i++;
    if (!envp[i])
        error_message("PATH not found");
    path_line = ft_strdup(envp[i]);
    path_line = ft_strchr(path_line, '=');
    *path = ft_split(path_line, ':');
//     free(path_line);
    path_line = NULL;
}

int		main(int argc, char **argv, char **envp)
{
    char **cmd_path;

	int j = 0;
	while (envp[j])
	{
		printf("envp[%d] = [%s]\n", j, envp[j]);
		j++;
	}

    make_env_path(&cmd_path, envp);
    

    int i = 0;
    while (cmd_path[i])
    {
	printf("%s\n", cmd_path[i]);
	i++;
    }
//     check_arg(argc, argv);
//     pipex(argc, argv, envp);
}
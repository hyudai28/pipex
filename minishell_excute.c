#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <errono.h>
#include <stdbool.h>

void    error_message(char *errmsg, int errno)
{
    printf("%s\n", errmsg);
    exit(1);
}

//execveで失敗してもExitはされずに次の行に進む。その代わりにerrnoにエラーナンバーが格納されるのでチェックする必要がある
//https://linuxjm.osdn.jp/html/LDP_man-pages/man2/wait.2.html?
int     minishell_excute(char *line, char **envp)
{
    int     pid;
    int     status;
    char    *tmp;
    char    *path;

    pid = fork();
    if (pid < 0)
        error_message("fork faied\n");
    if (pid == 0)
    {
        errno = 0;
        path = ft_strnjoin("/bin/", line);
        execve(path, argv, envp);
        if (errno)
            error_message(strerror(errno), errno);
    }
    if (waitpid(pid, &status, 0) < 0)
    {
        error_message(strerror(errno), errno);
    }
    return (WEXITSTATUS(status));
}
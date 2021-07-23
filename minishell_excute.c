#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

# define CMD_IS_ECHO 1
# define CMD_IS_CD 2
# define CMD_IS_PWD 3
# define CMD_IS_EXPORT 4
# define CMD_IS_UNSET 5
# define CMD_IS_ENV 6
# define CMD_IS_EXIT 7
# define PIPE_NOTHING 0
# define PIPE_PREVIOUS 1
# define PIPE_BEHIND 2
# define PIPE_BOTH 3

/*
int check_builtin_cmd(char *cmd_line)
{
    if (ft_strncmp(cmd_line, "echo", 5))
        return (CMD_IS_ECHO);
    else if (ft_strncmp(cmd_line, "cd", 3))
        return (CMD_IS_CD);
    else if (ft_strncmp(cmd_line, "pwd", 4))
        return (CMD_IS_PWD);
    else if (ft_strncmp(cmd_line, "export", 7))
        return (CMD_IS_EXPORT);
    else if (ft_strncmp(cmd_line, "unset", 6))
        return (CMD_IS_UNSET);
    else if (ft_strncmp(cmd_line, "env", 4))
        return (CMD_IS_ENV);
    else if (ft_strncmp(cmd_line, "exit", 5))
        return (CMD_IS_EXIT);
    else
        return (0);
}

int pipe_to_excute(char **line, char **envp, int pipe)
{
    int     cmd;
    int     ret;

    cmd = check_builtin_cmd(line[0]);
    if (cmd)
    {
        //I haven't make it.
        //ret = builtin_cmd_excute(line, envp, cmd);
    }
    else
    {
        ret = bin_excute(line, envp, pipe);
    }
    return (ret);
}
*/

void    error_message(char *errmsg, int errno)
{
    printf("%s\n", errmsg);
    exit(1);
}

#include "./libft/libft.h"

char *cmd1[] = {"ls", "-l", NULL};
char *cmd2[] = {"grep", "pipe", NULL};

typedef struct s_list
{
    char **command;
    int     pipe_number;
    struct s_list *prev;
    struct s_list *next;
}           t_list;


//execveで失敗してもExitはされずに次の行に進む。その代わりにerrnoにエラーナンバーが格納されるのでチェックする必要がある
//https://linuxjm.osdn.jp/html/LDP_man-pages/man2/wait.2.html?
int     bin_excute(char **line, char **envp, int pip)
{
    int     pid;
    int     status;
    char    *tmp;
    char    *path;
    int     pp[2];

    //pipe(pp);
    pid = fork();
    if (pid < 0)
        error_message("fork faied\n", errno);
    if (pid == 0)
    {
        errno = 0;
        path = ft_strnjoin("/bin/", line[0], 10);
        execve(path, line, envp);
        //if (errno)
            //error_message(strerror(errno), errno);
    }
    if (waitpid(pid, &status, 0) < 0)
    {
        //error_message(strerror(errno), errno);
    }
    return (WEXITSTATUS(status));
}

int     main(void)
{
    extern char **environ;
    char **envp = environ;

    bin_excute(cmd1, envp, 1);
}
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
	fprintf(stderr, "%s\n", err_msg);
	exit(1);
}

int	file_appropriate(char *infile, char *outfile)
{
    int     infile_perm;
    int     outfile_perm;

    infile_perm = access(infile, R_OK);
    outfile_perm = access(outfile, W_OK);
    if (outfile_perm)
    {
        if (access(outfile, F_OK))
            outfile_perm = 0;
    }
	return (infile_perm + outfile_perm);
}



void    check_arg(int argc, char **argv)
{
	if (file_appropriate(argv[1], argv[argc - 1]))
        error_message("permission denied: argv[1] or argv[4]");
	if (argc < 5)
		error_message("argument error");
}

void	split_free(char **dest)
{
    int i;

    i = 0;
    while (dest[i])
        i++;
	while (i > 0)
	{
		free(dest[i - 1]);
        dest[i - 1] = NULL;
		i--;
	}
	free(dest);
    dest = NULL;
}

void    free_cmds(char **cmd, char *path)
{
    split_free(cmd);
    free(path);
    path = NULL;
}

void    set_input_fd(int infile_fd, int *pipe_fd)
{
    close(0);
    dup2(infile_fd, 0);
    close(infile_fd);
    // close(pipe_fd[0]);
}

void    set_output_fd(int *pipe_fd)
{
    close(1);
    dup2(pipe_fd[1], 1);
    close(pipe_fd[1]);
}

char *get_path(char *cmd)
{
    return (cmd);
}

char *ft_pathjoin(char *bin_path, char *cmd)
{
    char *add_slash;
    char *ret_path;

    add_slash = ft_strjoin(bin_path, "/");
    if (!add_slash)
        error_message(strerror(errno));
    ret_path = ft_strjoin(add_slash, cmd);
    free(add_slash);
    add_slash = NULL;
    if (!ret_path)
        error_message(strerror(errno));
    return (ret_path);
}

char *set_command(char ***cmd, char *argv, char **bin_path)
{
    char    *path;
    int     path_i;
    int     access_ret;

    *cmd = ft_split(argv, ' ');
    if (!cmd)
        error_message(strerror(errno));
    path_i = 0;
    while (bin_path[path_i])
    {
        path = ft_pathjoin(bin_path[path_i], *cmd[0]);
        access_ret = access(path, X_OK);
        if (access_ret == 0)
            return (path);
        free(path);
        path = NULL;
        path_i++;
    }
    error_message("this command is not found");
    return (NULL);
}

void    pipex(int argc, char **argv, char **envp, char **bin_path)
{
    int infile_fd;
    int outfile_fd;
    int pipe_fd[2];
    int arg_i;
    char **cmd;
    char *path;
    pid_t   pid;

    arg_i = 2;
    infile_fd = open(argv[1], O_RDONLY);
    if (infile_fd < 0)
        error_message(strerror(errno));
    // pipe(pipe_fd);
    // if (pipe_fd < 0)
        // error_message(strerror(errno));
    while (arg_i < argc - 1)
    {
        pipe(pipe_fd);
        if (pipe_fd < 0)
            error_message(strerror(errno));
        pid = fork();
        if (pid < 0)
            error_message(strerror(errno));
        if (pid == 0)
        {
            if (arg_i == 2)
                set_input_fd(infile_fd, pipe_fd);
            if (arg_i == argc - 2)
            {
                outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT);
                dup2(outfile_fd, 1);
                close(outfile_fd);
            }
            else
                set_output_fd(pipe_fd);
            path = set_command(&cmd, argv[arg_i], bin_path);
            if (execve(path, cmd, envp))
                error_message(strerror(errno));
        }
        else
        {
            wait(NULL);
            if (!(arg_i == argc - 2))
            {
                dup2(pipe_fd[0], 0);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
        }
        arg_i++;
    }
}

void    make_env_path(char ***path, char **envp)
{
    //envpからPATHの行を抜き出す
    int i;
    char *path_line;
    size_t  find_slash;

    i = 0;
    while (ft_strncmp(envp[i], "PATH", 4))
        i++;
    if (!envp[i])
        error_message("PATH not found");
    path_line = ft_strdup(envp[i]);
    find_slash = gnl_strchr(path_line, '/');
    *path = ft_split(envp[i] + find_slash, ':');
    free(path_line);
    path_line = NULL;
}

int		main(int argc, char **argv, char **envp)
{
    char **cmd_path;

    check_arg(argc, argv);
    make_env_path(&cmd_path, envp);
    pipex(argc, argv, envp, cmd_path);
    // system("leaks a.out");
}
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

//int	command_appropriate(char *cmd1, char *cmd2)
//{
//    (void)cmd1;
//    (void)cmd2;
//	return (0);
//}

void    check_arg(int argc, char **argv)
{
	if (file_appropriate(argv[1], argv[argc - 1]))
        error_message("permission denied: argv[1] or argv[4]");
    //if (command_appropriate(argv[2], argv[3]))
    //    error_message("command not found: ");
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
    //close(0);
    dup2(infile_fd, 0);
    close(infile_fd);
    close(pipe_fd[0]);
}

void    set_output_fd(int *pipe_fd)
{
    //close(1);
    dup2(pipe_fd[1], 1);
    close(pipe_fd[1]);
}

char *get_path(char *cmd)
{

}

void set_command(char ***cmd, char **path, char *argv)
{
    *cmd = ft_split(argv, ' ');
    if (!cmd)
        write(2, "break\n", 6);
    *path = ft_strjoin("/usr/bin/", *cmd[0]);
}

void    pipex(int argc, char **argv, char **envp)
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
    pipe(pipe_fd);
    if (pipe_fd < 0)
        error_message(strerror(errno));
    while (arg_i < argc - 1)
    {
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
            set_command(&cmd, &path, argv[arg_i]);
            if (execve(path, cmd, envp))
                write(2, "execve_error\n", 13);
                //error_message(strerror(errno));
        }
        else
        {
            wait(NULL);
            //if (!(arg_i == argc - 2))
            //{
                dup2(pipe_fd[0], 0);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
                //split_free(cmd);
                // free(path);
                // path = NULL;
            //}
        }
        arg_i++;
    }
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
    *path = ft_split(envp, ':');
    free(path_line);
    path_line = NULL;
}

int		main(int argc, char **argv, char **envp)
{
    char **cmd_path;

    make_env_path(&cmd_path, envp);    
    check_arg(argc, argv);
    pipex(argc, argv, envp);
}
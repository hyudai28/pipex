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

void    pipex(int argc, char **argv, char **envp)
{
    int infile_fd;
    int outfile_fd;

//   /*
   char **cmd1;
   char **cmd2;
   char *path;
   char *path2;

    cmd1 = ft_split(argv[2], ' ');
    cmd2 = ft_split(argv[3], ' ');
    path = ft_strjoin("/bin/", cmd1[0]);
    path2 = ft_strjoin("/bin/", cmd2[0]);

    int pipe_fd[2];
    pid_t pid;

    pipe(pipe_fd);
    if (pipe_fd < 0)
        error_message(strerror(errno));
    pid = fork();
    if (pid < 0)
        error_message(strerror(errno));
    if (pid == 0)
    {
        infile_fd = open(argv[1], O_RDONLY);
        if (infile_fd < 0)
            error_message(strerror(errno));
        //close(0);
        dup2(infile_fd, 0);
        close(infile_fd);
        close(pipe_fd[0]);
        //close(1);
        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);
        if (execve(path, cmd1, envp))
            error_message(strerror(errno));
    }
    else
    {
        wait(NULL);
        close(0);
        dup2(pipe_fd[0], 0);
        close(pipe_fd[1]);

        outfile_fd = open(argv[4], O_WRONLY);
        close(1);
        dup2(outfile_fd, 1);
        close(outfile_fd);
        if (execve(path2, cmd2, envp))
            error_message(strerror(errno));
    }
}


int		main(int argc, char **argv, char **envp)
{
    check_arg(argc, argv);
    pipex(argc, argv, envp);
}
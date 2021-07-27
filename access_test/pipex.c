#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>

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

int	command_appropriate(char *cmd1, char *cmd2)
{
	return (0);
}

/*
int     bin_excute(char **line, char **envp, int pip)
{
    int     pid;
    int     status;
    char    *tmp;
    char    *path;
    int     pp[2];

    pid = fork();
    if (pid < 0)
        error_message("fork faied\n");
    if (pid == 0)
    {
        errno = 0;
        path = ft_strnjoin("/bin/", line[0], 10);
        execve(path, line, envp);
    }
    if (waitpid(pid, &status, 0) < 0)
    {
        //error_message(strerror(errno));
    }
    return (WEXITSTATUS(status));
}
*/

int		main(int argc, char **argv, char **envp)
{
	int		ret;

	ret = file_appropriate(argv[1], argv[4]);
	if (!ret)
		ret = command_appropriate(argv[2], argv[3]);
	if (ret)
		error_message("Err.\narg is bad");







    int infile_fd;
    int outfile_fd;
    char *cmd1[2] = {"cat", NULL};
    char *cmd2[3] = {"grep", "infile",  NULL};
    char *path = "/bin/cat";
    char *path2 = "/bin/grep";

    int pipe_fd[2];
    pid_t pid;

    pipe(pipe_fd);
    if (pipe_fd < 0)
    {
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        infile_fd = open(argv[1], O_RDONLY);
        if (infile_fd < 0)
        {
            perror("open");
            close(infile_fd);
            exit(1);
        }
        close(0);
        dup2(infile_fd, 0);
        close(infile_fd);
        close(pipe_fd[0]);
        close(1);
        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);
        execve(path, cmd1, envp);
    }
    else
    {
        wait(NULL);
        close(0);
        dup2(pipe_fd[0], 0);
        close(pipe_fd[1]);
        execve(path2, cmd2, envp);
    }
}
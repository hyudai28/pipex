#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>

void	error_message(char *err_msg, int errno)
{
	printf("%s\n", err_msg);
	exit (1);
}

int	file_appropriate(char *infile, char *outfile)
{
	return (0);
}

int	command_appropriate(char *cmd1, char *cmd2)
{
	return (0);
}

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

int		main(int argc, char **argv, char **envp)
{
	int		ret;

	ret = file_appropriate(argv[1], argv[4]);
	if (!ret)
		ret = command_appropriate(argv[2], argv[3]);
	if (ret)
		error_message("Err.\narg is bad\n", errno);
}
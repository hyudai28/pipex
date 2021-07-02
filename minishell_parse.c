#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	pid_t	pid;
	extern char **environ;

//	char *argv[3];
	char *argv[2];
	if ((pid = fork()) < 0)
	{
		perror("fork failed");
		return (1);
	}
	else if (pid == 0)
	{
		printf("ok from child\n");
		//argv[0] = "echo";
		argv[0] = "echo";
		//argv[1] = "message from echo program";
		argv[1] = NULL;
		//argv[2] = NULL;
		//execve("/bin/echo", argv, environ);
		execve("/bin/ls", argv, environ);
		_exit(1);
	}
	printf("parent: child process pid = %d\n", pid);
			
}

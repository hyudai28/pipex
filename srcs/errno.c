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

int	main(void)
{
	int err_i;

	err_i = 0;
	while (err_i < 135)
	{
		printf("errno[%d] = [%s]\n", err_i, strerror(err_i));
		err_i++;
	}
}
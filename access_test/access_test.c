#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int		acRET_000;
	int		acRET_777;
	int		acRET_nothing;

	acRET_000 = access(argv[1], R_OK);
	acRET_777 = access(argv[2], W_OK);
	acRET_nothing = access(argv[3], F_OK);

	printf("%s => [%d]\n", argv[1], acRET_000);
	printf("%s => [%d]\n", argv[2], acRET_777);
	printf("%s    => [%d]\n", argv[3], acRET_nothing);
}
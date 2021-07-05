#include <stdio.h>

int		main(int argc, char **argv)
{
	int i = 0;

	while (i < argc)
	{
		printf("line[%d]=%s\n", i, argv[i]);
		i++;
	}

}

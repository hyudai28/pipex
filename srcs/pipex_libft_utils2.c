#include "pipex.h"

//libft utils
void	split_free(char **dest)
{
    int i;

    i = 0;
    while (dest[i] != NULL)
	{
        i++;
	}
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


char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		size;

	c = (char)c;
	i = 0;
	size = ft_strlen(s) + 1;
	while (i < size)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

size_t	gnl_strchr(const char *s, int c)
{
	int		i;

	c = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

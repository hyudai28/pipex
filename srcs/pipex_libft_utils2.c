/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_libft_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:17:46 by hyudai            #+#    #+#             */
/*   Updated: 2021/10/16 23:15:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	split_free(char **dest)
{
	int	i;

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

void	free_cmds(char **cmd, char *path)
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
	return (0);
}

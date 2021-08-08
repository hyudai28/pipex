/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:09:45 by hyudai            #+#    #+#             */
/*   Updated: 2021/08/08 16:22:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_split_count(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static void	ft_set(char const *s, char **dest, char c, int count)
{
	int		i;
	int		j;

	i = 0;
	while (*s != '\0' && i != count)
	{
		j = 0;
		while (*s == c)
			s++;
		while ((*s != '\0') && (*s != c))
		{
			dest[i][j] = *s;
			s++;
			j++;
		}
		dest[i][j] = '\0';
		i++;
	}
	dest[i] = NULL;
}

static void	ft_split_free(char **dest, int i)
{
	while (i > 0)
	{
		free(dest[i - 1]);
		i--;
	}
	free(dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**dest;

	if (s == NULL)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_split_count(s, c) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < (ft_split_count(s, c)))
	{
		dest[i] = (char *)malloc(ft_strlen(s) + 1);
		if (dest[i] == NULL)
		{
			ft_split_free(dest, i);
			return (NULL);
		}
		i++;
	}
	ft_set(s, dest, c, ft_split_count(s, c));
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:03:24 by hyudai            #+#    #+#             */
/*   Updated: 2021/07/05 20:03:39 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include <stdio.h>
#include "./libft/libft.h"


typedef struct s_tree
{
	char	*name;
	struct s_tree **childs;
	int		size;
	int		length;
}				t_tree;

typedef struct s_ltree
{
	int				pipe;
	char			*name;
	struct s_ltree	**child;
	struct s_ltree	*next;
}				t_ltree


void	add_tree(t_ltree *node)
{

}

int main(int argc, char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		printf("line[%d]=%s\n", i, argv[i]);
		i++;
	}
}

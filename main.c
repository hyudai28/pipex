/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:03:24 by hyudai            #+#    #+#             */
/*   Updated: 2021/07/03 03:03:18 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include <stdio.h>

int	pipe_error(char ** argv)
{

	return (0);
}

int	command_check(char *argv)
{

	return (0);
}

char	**set_arg(char **arg, int i)
{
	char	**prs_arg;
	int		arg_index;
	int		prs_index;
	int		command_ret;

	arg_index = 0;
	prs_index = 0;
	prs_arg = (char *)malloc(i + 1);
	if (!prs_arg)
		return (1);
	while (arg[arg_index])
	{
		command_ret = command_check(arg[arg_index]);
		if (command_ret)
		{
			prs_index = 0;
			prs_arg[prs_index] = ft_strdup(arg[arg_index]);
			prs_index++;
			arg_index++;
		}
		else
		{
			prs_arg[prs_index] = ft_strdup(arg[arg_index]);
			arg_index++;
		}
	}
	return (prs_arg);
}

int main(int argc, char **argv)
{
	int i;
	int	count;
	char **prs_arg;

	i = 0;
	count = 0;
	pipe_error(char **argv);
	while (argv[i])
	{
		if (command_check(*argv))
			count++;
		i++;
	}
	prs_arg = set_arg(argv, i)

	/*
	while (i < argc)
	{
		printf("line[%d]=%s\n", i, argv[i]);
		i++;
	}
	*/
}

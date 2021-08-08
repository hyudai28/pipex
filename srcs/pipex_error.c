/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:18:08 by hyudai            #+#    #+#             */
/*   Updated: 2021/08/09 02:07:52 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//error
void	error_message(char *err_msg)
{
	fprintf(stderr, "%s\n", err_msg);
	exit(1);
}

int	file_appropriate(char *infile, char *outfile)
{
	int	infile_perm;
	int	outfile_perm;

	infile_perm = access(infile, R_OK);
	outfile_perm = access(outfile, W_OK);
	if (outfile_perm)
	{
		if (access(outfile, F_OK))
			outfile_perm = 0;
	}
	return (infile_perm + outfile_perm);
}

void	check_arg(int argc, char **argv)
{
	if (file_appropriate(argv[1], argv[argc - 1]))
		error_message("permission denied: argv[1] or argv[4]");
	if (argc < 5)
		error_message("argument error");
}

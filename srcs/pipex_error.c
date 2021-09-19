/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:18:08 by hyudai            #+#    #+#             */
/*   Updated: 2021/09/19 15:08:55 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//error
void	error_message(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
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
	if (argc < 5)
		error_message("too few args");
	if (file_appropriate(argv[1], argv[argc - 1]))
		error_message("open error\nmaybe...\n\
		1.permission denied->infile & outfile argument\n\
		2.infile is not found\n");
	if (argc < 5)
		error_message("argument error");
}

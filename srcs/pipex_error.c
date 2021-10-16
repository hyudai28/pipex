/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:18:08 by hyudai            #+#    #+#             */
/*   Updated: 2021/10/17 02:20:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define THIS_FILE_IS_DIR 1

//error
void	error_message(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	exit(1);
}

int	dir_check(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR);
	close(fd);
	if (fd == -1)
		return (THIS_FILE_IS_DIR);
	return (0);
}

int	file_appropriate(char *infile, char *outfile)
{
	int	infile_perm;
	int	outfile_perm;
	int	there_is_a_file;

	there_is_a_file = 0;
	infile_perm = access(infile, R_OK);
	outfile_perm = access(outfile, W_OK);
	if (outfile_perm)
	{
		there_is_a_file = access(outfile, F_OK);
		if (there_is_a_file)
			outfile_perm = 0;
	}
	if (!outfile_perm && !there_is_a_file)
		outfile_perm = dir_check(outfile);
	if (!infile_perm)
		infile_perm = dir_check(infile);
	return (infile_perm + outfile_perm);
}

void	check_arg(int argc, char **argv)
{
	if (argc < 5)
		error_message("too few args\n");
	if (file_appropriate(argv[1], argv[argc - 1]))
		error_message("open error\nmaybe...\n\
		1.permission denied->infile & outfile argument\n\
		2.infile is not found\n\
		3.infile outfile is a directly\n");
	if (argc < 5)
		error_message("argument error\n");
}

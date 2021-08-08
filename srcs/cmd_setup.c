/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:15:43 by hyudai            #+#    #+#             */
/*   Updated: 2021/08/09 02:09:02 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_input(int infile_fd, int arg_i)
{
	if (arg_i == 2)
	{
		close(STDIN_FILENO);
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
	}
}

char	*ft_pathjoin(char *bin_path, char *cmd)
{
	char	*add_slash;
	char	*ret_path;

	add_slash = ft_strjoin(bin_path, "/");
	if (!add_slash)
		error_message(strerror(errno));
	ret_path = ft_strjoin(add_slash, cmd);
	free(add_slash);
	add_slash = NULL;
	if (!ret_path)
		error_message(strerror(errno));
	return (ret_path);
}

char	*set_command(char ***cmd, char *argv, char **bin_path)
{
	char	*path;
	int		path_i;
	int		access_ret;

	*cmd = ft_split(argv, ' ');
	if (!cmd)
		error_message(strerror(errno));
	path_i = 0;
	while (bin_path[path_i])
	{
		path = ft_pathjoin(bin_path[path_i], *cmd[0]);
		access_ret = access(path, X_OK);
		if (access_ret == 0)
			return (path);
		free(path);
		path = NULL;
		path_i++;
	}
	error_message("this command is not found");
	return (NULL);
}

void	setup_output(char **argv, int argc, int arg_i, int *pipe_fd)
{
	int	outfile_fd;

	if (arg_i == argc - 2)
	{
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
	else
	{
		close(STDOUT_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

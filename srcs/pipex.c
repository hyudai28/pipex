/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:18:33 by hyudai            #+#    #+#             */
/*   Updated: 2021/10/14 18:44:07 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_parent(int *pipe_fd, int argc, int arg_i)
{
	wait(NULL);
	if (!(arg_i == argc - 2))
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	cmd_excute(char **argv, char **bin_path, char **envp, int arg_i)
{
	char	*path;
	char	**cmd;

	path = set_command(&cmd, argv[arg_i], bin_path);
	if (execve(path, cmd, envp))
		error_message(strerror(errno));
}

void	pipex(int argc, char **argv, char **envp, char **bin_path)
{
	int		infile_fd;
	int		pipe_fd[2];
	int		arg_i;
	pid_t	pid;

	arg_i = 1;
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		error_message(strerror(errno));
	while (++arg_i < argc - 1)
	{
		if (pipe(pipe_fd))
			error_message(strerror(errno));
		pid = fork();
		if (pid < 0)
			error_message(strerror(errno));
		if (pid == 0)
		{
			setup_input(infile_fd, arg_i);
			setup_output(argv, argc, arg_i, pipe_fd);
			cmd_excute(argv, bin_path, envp, arg_i);
		}
		else
			do_parent(pipe_fd, argc, arg_i);
	}
}

void	make_env_path(char ***path, char **envp)
{
	int		i;
	char	*path_line;
	size_t	find_slash;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		error_message("PATH not found");
	path_line = ft_strdup(envp[i]);
	find_slash = gnl_strchr(path_line, '/');
	*path = ft_split(envp[i] + find_slash, ':');
	free(path_line);
	path_line = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd_path;

	check_arg(argc, argv);
	make_env_path(&cmd_path, envp);
	pipex(argc, argv, envp, cmd_path);
}

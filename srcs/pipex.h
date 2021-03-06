/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:44:16 by hyudai            #+#    #+#             */
/*   Updated: 2021/10/16 23:18:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

# define ERR_PATH "PATH not found\n"
# define ERR_CMD "this command is not found\n"

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
size_t	gnl_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void	split_free(char **dest);
void	free_cmds(char **cmd, char *path);
void	error_message(char *err_msg);
int		file_appropriate(char *infile, char *outfile);
void	check_arg(int argc, char **argv);
void	setup_input(int infile_fd, int arg_i);
char	*ft_pathjoin(char *bin_path, char *cmd);
char	*set_command(char ***cmd, char *argv, char **bin_path);
void	setup_output(char **argv, int argc, int arg_i, int *pipe_fd);
void	do_parent(int *pipe_fd, int argc, int arg_i);
void	cmd_excute(char **argv, char **bin_path, char **envp, int arg_i);
void	pipex(int argc, char **argv, char **envp, char **bin_path);
void	make_env_path(char ***path, char **envp);

#endif

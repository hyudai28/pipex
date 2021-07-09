#include <stdlib.h>
#include <string.h>
#include <imostd.h>
#include <unistd.h>
#include <stdio.h>
#include "./libft/libft.h"


typedef enum
{
	HEAD,
	TAIL,
	EXPANDABLE_DQ,
	NONEXPANDABLE_SQ,
	EXPANDABLE,
	PIPE,
	READIRECT,
}		t_token_type;

typedef struct s_token
{
	//struct s_token	*prev;
	struct s_token	*next;
	t_token_type	type;
	char			*word;
	size_t			word_len;
}				t_token;

typedef struct s_parcers
{
	struct	s_parcers	*prev;
	struct	s_parcers	*next;
	int					type;
	char				**command;
	//t_redirect		*redirect;
}				t_parcers;

char	*command_to_tmp_lines(char *dest, char *src)
{
	char	*joined_que;
	char	*joined_str;

	joined_str = ft_strjoin(dest, src);
	free(dest);
	joined_que = ft_strjoin(joined_str, "??");
	free(joined_str);
	return (joined_que);
}

int		count_array_func(char *src)
{
	int	count_array;
	int	i;

	i = 0;
	count_array = 0;
	while (src[i])
	{
		if (src[i] == '?' && src[i + 1] == '?')
		{
			count_array += 1;
			i++;
		}
		i++;
	}
	return (count_array);
}

char	*copy_to_que(char *src, int *char_i)
{
	char	*dest;
	int		copy_i;

	dest = malloc(ft_strlen(src) + 1);
	copy_i = 0;
	while (src[*char_i])
	{
		if (src[*char_i] == '?' && src[*char_i + 1] == '?')
		{
			dest[copy_i] = '\0';
			*char_i += 2;
			return (dest);
		}
		dest[copy_i] = src[*char_i];
		copy_i++;
		*char_i++;
	}
	dest[copy_i] = '\0';
	return (dest);
}

char	**array_to_two_array(char *src)
{
	char	**ret_array;
	int		count_array;
	int		str_i;
	int		char_i;

	count_array = count_array_func(src);
	ret_array = malloc((char **) count_array + 1);
	str_i = 0;
	char_i = 0;
	while (str_i < count_array)
	{
		ret_array[i] = copy_to_que(src, &char_i);
		i++;
	}
	*ret_array = NULL;
	return (ret_array);
}

void	insert_token(t_token *token, t_parcers *prev)
{
	t_parcers	*new_node;
	int			command_count;
	char		*tmp_lines;

	new_node = (t_parcers){};
	prev->next = new_node;
	new_node->prev = prev;
	new_node->prev = NULL;
	tmp_lines = NULL;
	while (token->(*word) != '|')
	{
		if (token->(*word))
			break;
		tmp_lines = command_to_tmp_lines(tmp_lines, t_token->word);
		token = token->next;
	}
	new_node->command = array_to_two_array(tmp_lines);
}



int		parcer(t_token *token)
{
	t_parcers	HEAD;

	HEAD = (t_parcers){};
	if (token->word[0] != "|")
	{
		insert_token(token, HEAD);
	}
	else
	{
		insert_pipe(token, HEAD);
	}
}






/*
int	main(void)
{
	pid_t	pid;
	extern char **environ;

//	char *argv[3];
	char *argv[2];
	if ((pid = fork()) < 0)
	{
		perror("fork failed");
		return (1);
	}
	else if (pid == 0)
	{
		printf("ok from child\n");
		//argv[0] = "echo";
		argv[0] = "echo";
		//argv[1] = "message from echo program";
		argv[1] = NULL;
		//argv[2] = NULL;
		//execve("/bin/echo", argv, environ);
		execve("/bin/ls", argv, environ);
		_exit(1);
	}
	printf("parent: child process pid = %d\n", pid);
*/			
}

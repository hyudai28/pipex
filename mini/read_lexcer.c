#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

#define TRUE	1
#define FALSE	0
#define ERROR	-1

typedef	enum
{
	HEAD,
	TAIL,
	EXPANDABLE_DQ,
	NONEXPANDABLE_SQ,
	EXPANDABLE,
	PIPE,
	REDIRECT,
}	t_token_type;

typedef struct s_token
{
	//t_token			*prev;
	struct s_token	*next;
	t_token_type	type;
	char			*word;
	size_t			word_len;
} t_token;

typedef	struct s_flag
{
	int	dq_flag;
	int sq_flag;
	int	pipe;
	int	redirect;
	int	error;
}	t_flag;


void	ft_strlen_sq_dq(char *str, char quotation, t_token *new, t_flag *flag)
{
	size_t	len;
	int		i;
	int	count;

	count = 0;
	len = 0;
	i = -1;
	while(count != 2)
	{
		if (str[++i] == quotation)
			count++;
		if (str[i] == '\0')
		{
			new->word_len = ERROR;
		}
		else
			len++;
	}
	if (new->word_len != ERROR)
		new->word_len = len;
	else
		printf("ERROR  \"quotation has no pair\"\n");
	if (quotation == '"')
		new->type = EXPANDABLE_DQ;
	else
		new->type = NONEXPANDABLE_SQ;
	flag->dq_flag = FALSE;
	flag->sq_flag = FALSE;
}

void	ft_strlen_others(char *str, t_token *new)
{
	size_t	len;
	int		i;

	len = 0;
	i = -1;
	while(!ft_strchr("|>< \'\"\0", str[++i]))
		len++;
	new->word_len = len;
	new->type = EXPANDABLE;
}

void	ft_strlen_redirect(char *str, t_token *new, t_flag *flag)
{
	size_t	len;
	int	i;

	len = 0;
	if (!ft_strncmp(str, ">>", 2))
		new->word_len = 2;
	else if (!ft_strncmp(str, ">", 1))
		new->word_len = 1;
	else if (!ft_strncmp(str, "<<", 2))
		new->word_len = 2;
	else if (!ft_strncmp(str, "<", 1))
		new->word_len = 1;
	new->type = REDIRECT;
	flag->redirect = FALSE;
}

void	ft_strlen_pipe(t_token *new, t_flag *flag)
{
	new->word_len = 1;
	new->type = PIPE;
	flag->pipe = FALSE;
}

t_token	*new_token(t_flag *flag, t_token *cur, char **str)
{
	t_token	*new;
	size_t	len;	

	new = (t_token *)malloc(sizeof(t_token));
	ft_memset(new, 0, sizeof(t_token));
	cur->next = new;
	if (**str == '\0')
	{
		new->type = TAIL;
		return new;
	}
	if (flag->dq_flag == TRUE)
		ft_strlen_sq_dq(*str, '"', new, flag);
	else if (flag->sq_flag == TRUE)
		ft_strlen_sq_dq(*str, '\'', new, flag);
	else if (flag->pipe == TRUE)
		ft_strlen_pipe(new, flag);
	else if (flag->redirect == TRUE)
		ft_strlen_redirect(*str, new, flag);
	else
		ft_strlen_others(*str, new);
	new->word = (char *)malloc(len + 1);
	ft_strlcpy(new->word, *str, new->word_len + 1);
	if (new->word_len == ERROR)
		return new;
	len = new->word_len;
	while (len--)
		(*str)++;
	return new;
}

void	debug2(t_token *tmp)
{
	printf("token : %s\n", tmp->word);
	/*
	printf("token_len : %d\n", (int)tmp->word_len);
	printf("<token type> HEAD=0,TAIL=1,EXPANDABLE_DQ=2,NONEXPANDABLE_SQ=3,EXPANDABLE=4,PIPE=5,REDIRECT=6\n");
	printf("token type: %d\n", tmp->type);
	printf("--------------------------\n");
	*/
}

void	debug1(t_token *tmp)
{
	printf("token : %s\n", tmp->word);
	printf("token_len : %d\n", (int)tmp->word_len);
	printf("<token type> HEAD=0,TAIL=1,EXPANDABLE_DQ=2,NONEXPANDABLE_SQ=3,EXPANDABLE=4,PIPE=5,REDIRECT=6\n");
	printf("token type: %d\n", tmp->type);
	printf("--------------------------\n");
}

int	lexcer(char *argv)
{
	t_token	*head;
	t_flag flag;

	char *str = argv;
	ft_memset(&flag, 0, sizeof(t_flag));
	head = (t_token *)malloc(sizeof(t_token));
	ft_memset(head, 0, sizeof(t_token));
	head->next = NULL;
	head->type = HEAD;
	head->word = NULL;
	t_token *cur = head;
	//printf("\n\n\n<<Line of commands>>\n");
	//printf("%s\n", str);
	//printf("<<First word of each token>>\n\t");
	while(*str != '\0')
	{
		while (isspace(*str))
			str++;
		if (*str == '"')
			flag.dq_flag = TRUE;
		else if (*str == '\'')
			flag.sq_flag = TRUE;
		else if (*str == '>' || *str == '<')
			flag.redirect = TRUE;
		else if (*str == '|')
			flag.pipe = TRUE;
		//printf("%c, ", *str);
		cur = new_token(&flag, cur, &str);
		if (cur->word_len ==  ERROR)
			return(0);
	}
	//printf("\n\n");
	cur = new_token(&flag, cur, &str);
	t_token *tmp = head;
	while (tmp->type != TAIL)
	{
		debug1(tmp);
		//debug2(tmp);
		tmp = tmp->next;
	}
	debug1(tmp);
	//debug2(tmp);
	//printf("End Token List\n");
	return (0);
}

int main(void)
{
    char *command;

    while (1)
    {
		command = readline("minishell > ");
        if (command == NULL)
        {
            //exitの処理
        }
        else if (strlen(command) > 0)
        {
            add_history(command);
			lexcer(command);
            // 処理
        }
        free(command);
    }
    return 0;
}
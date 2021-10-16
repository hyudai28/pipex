NAME := pipex

CC := gcc
CFLAGS := -Wall -Werror -Wextra

SRCS := ft_split.c
SRCS += cmd_setup.c
SRCS += pipex_error.c
SRCS += pipex_libft_utils.c
SRCS += pipex_libft_utils2.c
SRCS += pipex.c

OBJS := ${SRCS:.c=.o}
BONUSOBJS := ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		rm -f $(OBJS) $(BONUSOBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
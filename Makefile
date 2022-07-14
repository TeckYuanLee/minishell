NAME	=	minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include -Iincludes#-fsanitize=address -g3
LDFLAGS = -L/usr/include -L/usr/local/opt/readline/lib -lreadline
ARFLAGS	= 	rcs

LIBFT_PATH = libft/
LIBFT = libft/libft.a

SRCS	=	$(wildcard srcs/*.c)
OBJS	=	$(SRCS:srcs/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	@make re -C $(LIBFT_PATH)

obj/%.o:	srcs/%.c
		@mkdir -p obj
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		@rm -f $(OBJS)

fclean:	clean
		@rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 14:50:07 by telee             #+#    #+#              #
#    Updated: 2021/06/27 10:13:38 by telee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
FLAGS		= -Wall -Werror -Wextra -I. -c
SRC			= $(wildcard srcs/*.c)
OBJ			= $(SRC:srcs/%.c=obj/%.o)

all: 		$(NAME)

$(NAME): 	$(OBJ)
				@ar rcs $(NAME) $(OBJ)

obj/%.o:	srcs/%.c
				@gcc $(FLAGS) -c $< -o $@ -Iincludes ##libft.h get_next_line.h

clean:
				@rm -f obj/*.o

fclean: 	clean
				@rm -f $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re

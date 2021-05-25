# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:43 by user42            #+#    #+#              #
#    Updated: 2021/05/25 14:58:59 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#CFLAGS = -Wall -Wextra -Werror
SRC = 	minishell.c parser.c list.c utils.c free.c errors.c checker.c debug.c hub.c ./tokens/concat_tokens.c ./tokens/get_token.c ./tokens/utils_concat_tokens.c env.c
NAME = ft_minishell
LIB = ar rcs

all : $(NAME)

$(NAME):	
			@$(CC) $(CFLAGS) ${SRC} -o $(NAME)
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled]"

%.o: %.c
			$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@rm -f *.o

fclean:	clean
			@rm -f $(NAME)
			@rm -f a.aout
			
re:			fclean all
		
exec:		re
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME)
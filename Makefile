# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:43 by user42            #+#    #+#              #
#    Updated: 2021/05/20 17:07:34 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = 	minishell.c parser.c list.c utils.c free.c errors.c checker.c debug.c
NAME = ft_minishell
LIB = ar rcs

all : $(NAME)

$(NAME):	
			@$(CC) $(CFLAGS) $(MFLAGS) -o $(NAME) ${SRC}
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
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME)
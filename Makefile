# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walker <walker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:43 by user42            #+#    #+#              #
#    Updated: 2021/08/30 18:11:04 by walker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#CFLAGS = -Wall -Wextra -Werror
SRC = 	minishell.c parser.c free.c errors.c checker.c debug.c hub.c ./tokens/concat_tokens.c ./tokens/get_token.c ./tokens/utils_concat_tokens.c env.c
NAME = ft_minishell
LIB = ar rcs
LIBFT =	libft.a

all : $(NAME)

$(NAME):	
			@make -C ./libft
			@cp ./libft/libft.a $(LIBFT)
			@$(CC) $(CFLAGS) ${SRC} $(LIBFT) -o $(NAME) -lreadline
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled]"

%.o: %.c
			$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@rm -f *.o
			@make -C ./libft fclean

fclean:		clean
			@rm -f $(LIBFT)
			@rm -f $(NAME)
			@rm -f a.aout
			
re:			fclean all
		
exec:		re
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME)
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:43 by user42            #+#    #+#              #
#    Updated: 2021/09/28 14:24:19 by arapaill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
#CFLAGS =	-Wall -Wextra -Werror
SRC		=	minishell.c parser.c free.c errors.c \
			checker.c debug.c hub.c \
			./tokens/concat_tokens.c ./tokens/get_token.c \
			./tokens/utils_concat_tokens.c env.c cmd_unset.c \
			cmd_echo.c cmd_export.c
OBJ 	=	$(SRC:%.c=%.o)
NAME 	=	ft_minishell
LIBFT	=	libft.a

all : $(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled]"

$(LIBFT):	
			@make --no-print-directory -C ./libft
			@cp ./libft/libft.a $(LIBFT)

clean:
			@rm -f *.o
			@rm -f tokens/*.o
			@make --no-print-directory -C ./libft clean

fclean:		clean
			@make --no-print-directory -C ./libft fclean
			@rm -f $(LIBFT) $(NAME) a.aout
			
re:			fclean all
		
exec:		all
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME)
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
SRC		=	minishell.c free.c errors.c debug.c \
			./srcs/cmd/cmd_echo.c ./srcs/cmd/cmd_unset.c ./srcs/cmd/hub.c \
			./srcs/cmd_struct/ft_cmdadd_back.c ./srcs/cmd_struct/ft_cmdadd_front.c ./srcs/cmd_struct/ft_cmdlast.c ./srcs/cmd_struct/ft_cmdnew.c ./srcs/cmd_struct/ft_cmdsize.c ./srcs/cmd_struct/ft_cmdfirst.c \
			./srcs/env/env.c \
			./srcs/parsing/checker.c ./srcs/parsing/parser.c \
			./srcs/tokens/concat_tokens.c ./srcs/tokens/get_token.c ./srcs/tokens/utils_concat_tokens.c ./srcs/tokens/tokens.c
OBJ 	=	$(SRC:%.c=%.o)
NAME 	=	ft_minishell
LIBFT	=	libft.a

all : $(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) ./srcs/$(LIBFT) -lreadline
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled]"

$(LIBFT):	
			@make --no-print-directory -C ./srcs/libft
			@cp ./srcs/libft/libft.a ./srcs/$(LIBFT)

clean:
			@rm -f *.o
			@rm -f ./srcs/*/*.o
			@make --no-print-directory -C ./srcs/libft clean

fclean:		clean
			@make --no-print-directory -C ./srcs/libft fclean
			@rm -f $(NAME) a.aout srcs/${LIBFT}
			
re:			fclean all
		
exec:		all
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME)
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:16:14 by marvin            #+#    #+#             */
/*   Updated: 2021/05/12 16:16:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include <malloc.h>

# include "../libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

typedef enum e_token_type
{
	space,
	line_return,
	pipeline,
	semicolon,
	simple_redir_left,
	simple_redir_right,
	double_redir_left,
	double_redir,right,
	single_quote,
	double_quote,
	backslash,
	variable,
	literal

}	t_token_type;

typedef struct s_token
{
	void *value;
	t_token_type type;

}	t_token;

typedef struct	s_node
{
	t_token	*content;
	struct s_node	*next;
}	t_node;


typedef struct s_minishell
{
	t_node *list_input;
	char **env;
}	t_minishell;

t_minishell g_minishell;

/*
** g_minishell
*/

void	sh_pre(void);
int		main(int argc, char *argv, char **env);

/*
** parser
*/

t_bool	parsing(char *user_input);
void    tokenizer(char *input);
t_token *create_token(char *value, t_token_type type);

/*
**	env.c
*/

int		main_env();
void	print_env();
char	*get_value_env(char *name);
int 	add_env(char *name, char *value);


/*
** concat_tokens
*/

void    concat_tokens_all();
t_bool  concat_no_spaces();
t_bool	concat_tokens_quotes();

/*
** get_token
*/

t_token_type get_token_type(t_token *token);
void	*get_token_value(t_token *token);

/*
** utils_concat_tokens
*/

void	*join_two_tokens(t_token *token_1, t_token *token_2);
void	relink_nodes();

/*
** checker.c
*/

t_bool	checking_if_quotes_even();

/*
** errors.c
*/

void	error(char *error_text);

/*
** free.c
*/

void	free_list(void);

/*
** debug.c
*/

void	debug(void);

/*
** hub.c
*/

void	cmd_hub(void);

#endif
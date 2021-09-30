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
# include <string.h>
# include <stdlib.h>

# include "../srcs/libft/libft.h"

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
	double_redir_right,
	single_quote,
	double_quote,
	backslash,
	variable,
	literal,
	cmd_instr,
	none
}	t_token_type;

typedef struct s_token
{
	void			*value;
	t_token_type	type;
	int				pipe_in;
	int				pipe_out;

}	t_token;

typedef struct s_cmd
{
	t_token			*content;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_minishell
{
	t_cmd *list_input;
	char **env;
}	t_minishell;

t_minishell g_minishell;

/*
** minishell
*/

void	sh_pre(void);
int		main(int argc, char **argv, char **env);


/* 
**	cmd_struct 
*/

void	ft_cmdadd_back(t_cmd **alst, t_cmd *new);
void	ft_cmdadd_front(t_cmd **alst, t_cmd *new);
t_cmd	*ft_cmdlast(t_cmd *lst);
t_cmd	*ft_cmdnew(void *content);
size_t	ft_cmdsize(t_cmd *lst);
t_cmd	*ft_cmdfirst(t_cmd *lst);

/*
** parser
*/

t_bool	parsing(char *user_input);
void    tokenizer(char *input);

/*
**	env.c
*/

int		main_env();
void	print_env();
char	*get_value_env(char *name);
int 	add_env(char *name, char *value);
char 	**realloc_env(int size);
void	copy_env(int env_size, char **tmp);

/*
** concat_tokens
*/

void    concat_tokens_same_type();
void    concat_tokens_all();
t_bool  concat_no_spaces();
t_bool	concat_tokens_quotes();
void 	concat_tokens_var(void);
void	*join_two_tokens(t_token *token_1, t_token *token_2);
void	relink_nodes();

/*
** tokens
*/

t_token_type	get_token_type(t_token *token);
void			*get_token_value(t_token *token);
t_token			*create_token(char *value, t_token_type type);
t_token_type 	find_type(char c);

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
void	print_current_chain(void);

/*
** hub.c
*/

void	cmd_hub(void);
void    cmd_unset(t_cmd *list);
void	cmd_echo(t_cmd *list);
void	cmd_export(t_cmd *list);

#endif
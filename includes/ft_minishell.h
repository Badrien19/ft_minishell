/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
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

# define EXIT_SUCCESS 0

typedef enum e_bool
{
	False,
	True
} t_bool;

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

typedef struct	s_list
{
	t_token	*content;
	struct s_list	*next;
}	t_list;


typedef struct s_sys_infos
{
	t_list *list_input;
}	t_sys_infos;

t_sys_infos g_sys_infos;

/*
** minishell
*/

void	sh_pre(void);
int		main(int argc, char *argv, char **env);

/*
** parser
*/

void	parsing(char *user_input);
void    tokenizer(char *input);
t_token *create_token(char *value, t_token_type type);

/*
**	env.c
*/

int		main_env(char **env);

/*
** concat_tokens
*/

void    concat_tokens_all();
void    concat_no_spaces();
void    concat_tokens_quotes();

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
** utils
*/

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr(char *s, int fd);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);

/*
** lists
*/

void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

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

void    print_list(void);

/*
** hub.c
*/

void	cmd_hub(void);

#endif
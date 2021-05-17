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

# define BOOL signed int
# define TRUE 1
# define FALSE 0

<<<<<<< HEAD
typedef enum e_token_type
{
	space,
	pipeline,
	semicolon,
	simple_redir_left,
	simple_redir_right,
	double_redir_left,
	double_redir,right,
	single_quote,
	double_quote,
	backslash,
	literal

}	t_token_type;

typedef struct	s_list
{
	void	*value;
	struct s_list	*next;
}	t_list;


typedef struct s_token
{
	void *value;
	t_token_type type;

}	t_token;
=======
typedef enum	e_rdir
{
	none,
	left,
	right,
	rright,
	pipe	
}				t_rdir;

typedef struct 	s_cmd
{
	void		*cmd;
	void		*args;
	void		*result;

	t_rdir		redirect;

	t_cmd		*in;
	t_cmd		*out;
}				t_cmd;
>>>>>>> 31024987dfb63d21ce38e1fb8e8eb383adc60d25

/*
** parser
*/

void	parsing(char *user_input);

/*
** utils
*/

char	**ft_split(char const *s, char c);

/*
** minishell
*/

void	sh_pre(void);
int		main(int argc, char *argv[]);

/*
** libft
*/

void	ft_putstr(char *s, int fd);


/*
** init
*/

void    init_struct_cmd(t_cmd *cmd);

/*
** free
*/

void	free_cmd(t_cmd	*cmd);
void	cmdclear(t_cmd **cmd);

#endif
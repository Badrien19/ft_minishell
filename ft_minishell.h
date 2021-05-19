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
# include <limits.h>


# define EXIT_SUCCESS 0

# define BOOL signed int
# define TRUE 1
# define FALSE 0
# define PATH_MAX        4096

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


#endif
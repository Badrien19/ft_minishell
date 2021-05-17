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
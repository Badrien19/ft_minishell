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

#ifndef FT_MINISHELL
# define FT_MINISHELL

# include <unistd.h>
# include <stdio.h>
# include <dirent.h>

# define EXIT_SUCCESS 0

# define BOOL signed int
# define TRUE 1
# define FALSE 0

typedef enum e_rdir
{
	none,
	left,
	right,
	rright
	pipe	
}	t_rdir;

typedef struct	s_cmd
{
	void	*cmd;
	void	*args;
	void	*result;

	t_rdir	redirect;

	t_cmd	*in;
	t_cmd	*out;
}	t_cmd;


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
void	main(int argc, char *argv[]);

#endif
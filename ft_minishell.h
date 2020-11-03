#ifndef FT_MINISHELL
# define FT_MINISHELL

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>

typedef struct	s_env
{
    char			*name;
    void			*content;
    struct s_env	*next;
}				t_env;

typedef struct	s_rdir
{
	void 			*args;

	struct s_rdir	*next;
}				t_rdir

typedef struct	s_cmd
{
    void			**args;
	
	BOOL			is_pipped;
	BOOL			is_rdir;

	t_rdir			*in; // arg qui vient apres
	t_rdir			*out;
	// ? t_pipped
    struct s_cmd	*next;
}				t_cmd;

/*
** parser
*/

void	cmd_parser(char *cmd);

/*
** commands
*/

void	cmd_echo(char *cmd);
void	cmd_exit(char *cmd);
void	cmd_pwd();

# define BUFFER 10
#endif
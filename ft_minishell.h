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
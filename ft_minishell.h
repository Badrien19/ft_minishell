#ifndef FT_MINISHELL
# define FT_MINISHELL

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>

/*
** parser
*/

void    cmd_parser(char *cmd);

/*
** commands
*/

void    cmd_echo(char *cmd);
void    cmd_exit(char *cmd);
void    cmd_pwd();

# define BUFFER 10
#endif
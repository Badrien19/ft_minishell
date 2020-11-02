#ifndef FT_MINISHELL
# define FT_MINISHELL

# include "libft/libft.h"
# include "unistd.h"
# include "stdio.h"

/*
** parser
*/

int     cmd_parser(char *cmd);

/*
** commands
*/

void     cmd_echo(char *cmd);
void     cmd_exit(char *cmd);

# define BUFFER 10
#endif
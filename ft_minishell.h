#ifndef FT_MINISHELL
# define FT_MINISHELL

# include <unistd.h>
# include <stdio.h>
# include <dirent.h>

# define EXIT_SUCCESS 0

# define BOOL signed int
# define TRUE 1
# define FALSE 0

/*
** minishell
*/

void    sh_pre();
void	main(int argc, char *argv[]);

#endif
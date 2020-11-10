#ifndef FT_MINISHELL
# define FT_MINISHELL

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>

# define EXIT_SUCCESS 0

# define BOOL signed int
# define TRUE 1
# define FALSE 0

typedef struct	s_env // ---> enfaite tableau c'est mieux
{
    char			*name;
    void			*content;
    struct s_env	*next;
}				t_env;

typedef struct	s_rdir
{
	void 			*args;

	struct s_rdir	*next;
}				t_rdir;

typedef struct	s_cmd
{
    void			**args;
	
	BOOL			is_pipped;
	BOOL			is_rdir;

	t_rdir			*in; // arg qui vient apres
	t_rdir			*out;
//	t_pipped		*pip;

    struct s_cmd	*next;
}				t_cmd;

/*
** utils
*/

char	detect_quote(char *str);
char    *remove_quote(char *str);
size_t 	count_tok(char *str, char* charset);
BOOL	try_charset(char c, char *charset);
char	*copy_str(char *src, size_t size);
char	**sh_split_line(char *str, char* charset);

/*
** parser
*/

void	cmd_parser(char *cmd, t_env *lst);

/*
** commands
*/

void	cmd_echo(char *cmd);
void	cmd_exit(char *cmd);
void	cmd_pwd();

/*
** minishell
*/

int		main(int argc, char **argv);
void    sh_pre();
void	sh_loop();
void	print_lst(t_env *lst);


#endif
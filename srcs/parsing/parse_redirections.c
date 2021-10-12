#include "../../includes/ft_minishell.h"

void	check_redirection_and_pipe(void)
{
	check_simple_redirection_left();
	check_double_redirection_left();
	check_simple_redirection_right();
	check_double_redirection_right();
	while (is_there_pipe() == True)
	{
		check_pipe();
		g_minishell.list_input = g_minishell.list_input->next;
	}
}

void	check_simple_redirection_left(void) // Vérifier les mots après le <
{
	int		fd;

	fd = -1;
	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == simple_redir_left)
		{
			if (fd > 0)
				close(fd);
			if (verify_redir_parse_error() != 0)
				return ;
			fd = open(find_next_literal(1)->content->value, O_RDONLY);
			if (fd < 0)
			{
				parsing_error(3);
				return ;
			}
			if (find_next_cmd())
				find_next_cmd()->content->pipe_in = fd;
			else if (find_prev_cmd())
				find_prev_cmd()->content->pipe_in = fd;
			else
			{
				parsing_error(4);
				return ;
			}
		}
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

int		verify_redir_parse_error(void)
{
	int		fd;
	t_cmd 	*file;
	t_cmd	*current;

	current = g_minishell.list_input; 
	file = find_next_literal(1);
	if (file == NULL)
	{
		parsing_error(1);
		return (-1); // TEMP
	}
	g_minishell.list_input = file->next;
	if (find_next_literal(0))
	{
		parsing_error(2);
		return (-1); // TEMP
	}
	g_minishell.list_input = current;
	return (0);
}

void	check_simple_redirection_right(void)
{
	int		fd;

	fd = -1;
	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == simple_redir_right)
		{
			/* Verify the parsing
			** Verify the file
			** Open the file
			** Replace pipe_out of cmd
			*/ 
			if (fd > 0)
				close(fd);
			if (verify_redir_parse_error() != 0)
				return ;
			fd = open(find_next_literal(1)->content->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd < 0)
			{
				parsing_error(3);
				return ;
			}
			if (find_next_cmd())
				find_next_cmd()->content->pipe_out = fd;
			else if (find_prev_cmd())
				find_prev_cmd()->content->pipe_out = fd;
			else
			{
				parsing_error(4);
				return ;
			}
		}
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

void	check_double_redirection_right(void)
{
	int		fd;

	fd = -1;
	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == double_redir_right)
		{
			/* Verify the parsing
			** Verify the file
			** Open the file
			** Replace pipe_out of cmd
			*/ 
			if (fd > 0)
				close(fd);
			if (verify_redir_parse_error() != 0)
				return ;
			fd = open(find_next_literal(1)->content->value, O_CREAT | O_RDWR | O_APPEND);
			if (fd < 0)
			{
				parsing_error(3);
				return ;
			}
			if (find_next_cmd())
				find_next_cmd()->content->pipe_out = fd;
			else if (find_prev_cmd())
				find_prev_cmd()->content->pipe_out = fd;
			else
			{
				parsing_error(4);
				return ;
			}
		}
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

void	check_double_redirection_left(void)
{
	char	*end_redir;
	char	*buffer;
	int		fd[2];

	buffer = NULL;
	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == double_redir_left)
		{
			end_redir = find_next_literal(1)->content->value;
			pipe(fd);
			printf("end_redir : %s\n", end_redir);
			while (True)
			{
				buffer = readline("\033[1;32m>\033[0m ");
				write(fd[0], &buffer, ft_strlen(buffer));
				if (!ft_strcmp(buffer, end_redir))
					break ;
			}
			if (find_next_cmd())
				find_next_cmd()->content->pipe_in = fd[0];
			else if (find_prev_cmd())
				find_prev_cmd()->content->pipe_in = fd[0];
			else
			{
				parsing_error(4);
				return ;
			}
		}
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

t_bool	is_there_pipe(void)
{
	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == pipeline)
			return (True);
		g_minishell.list_input = g_minishell.list_input->next;
	}
	return (False);
}

void	check_pipe(void)
{
	int		fd[2];

	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == pipeline)
			break ;
		g_minishell.list_input = g_minishell.list_input->next;
	}
	if (find_prev_cmd()->content->pipe_out == STDOUT_FILENO)
	{
		if (pipe(fd) < 0)
		{
			perror("minishell");
			return ;
		}
		find_prev_cmd()->content->pipe_out = fd[0];
		find_next_cmd()->content->pipe_in = fd[1];
	}
	else
		find_next_cmd()->content->pipe_in = find_prev_cmd()->content->pipe_out;
}

/* Erreurs possibles :
** cmd > > file1 : parse error
** cmd > file1 file2 : too many arguments
** cmd1 > cmd2 : Fonctionne (le fichier cmd2 est créé)
**
*/
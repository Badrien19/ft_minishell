#include "../../includes/ft_minishell.h"

void	check_redirection_and_pipe(void)
{
	check_simple_redirection_left();
	check_simple_redirection_right();
	while (is_there_pipe() == True)
	{
		check_pipe();
		g_minishell.list_input = g_minishell.list_input->next;
	}
}

void	check_simple_redirection_left(void) // Vérifier les mots après le <
{
	t_cmd	*tmp;
	int		fd;
	int		prev_fd;

	fd = -1;
	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == simple_redir_left)
		{
			if (fd > 0)
				close(fd);
			fd = open(find_next_literal()->content->value, O_RDONLY);
			if (fd < 0)
			{
				perror("minishell");
				return ;
			}
			if (find_next_cmd())
				find_next_cmd()->content->pipe_in = fd;
			else if (find_prev_cmd())
				find_prev_cmd()->content->pipe_in = fd;
			else
			{
				write(2, "minishell: command not found.\n", 30); // TEMP
				return ;
			}
		}
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

void	check_simple_redirection_right(void) // Vérifier les mots après le >
{
	int		fd;
	int		prev_fd;

	fd = -1;
	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == simple_redir_right)
		{
			if (fd > 0)
				close(fd);
			fd = open(find_next_literal()->content->value, O_WRONLY);
			if (fd < 0)
			{
				perror("minishell");
				return ;
			}
			if (find_next_cmd())
				find_next_cmd()->content->pipe_out = fd;
			else if (find_prev_cmd())
				find_prev_cmd()->content->pipe_out = fd;
			else
			{
				write(2, "minishell: command not found.\n", 30); // TEMP
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
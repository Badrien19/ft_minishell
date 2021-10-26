/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:46:20 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/26 15:46:20 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	is_there_literal_for_file(void)
{
	t_cmd	*current;
	t_cmd	*file;

	current = g_minishell.list_input;
	file = find_next_literal(1);
	if (file == NULL)
	{
		parsing_error(MS_ERROR_PARSE);
		return (False);
	}
	g_minishell.list_input = current;
	return (True);
}

void	parse_simple_redirection_right(void)
{
	int	fd;

	fd = -1;
	if (fd > 0)
		close(fd);
	if (is_there_literal_for_file() == False)
		return ;
	fd = open(find_next_literal(1)->content->value,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		parsing_error(MS_ERROR_TO_PERROR);
		return ;
	}
	if (find_next_cmd())
		find_next_cmd()->content->pipe_out = fd;
	else if (find_prev_cmd())
		find_prev_cmd()->content->pipe_out = fd;
	else
	{
		parsing_error(MS_ERROR_NO_CMD);
		return ;
	}
}

void	parse_double_redirection_right(void)
{
	int	fd;

	fd = -1;
	if (fd > 0)
		close(fd);
	if (is_there_literal_for_file() == False)
		return ;
	fd = open(find_next_literal(1)->content->value,
			O_CREAT | O_RDWR | O_APPEND);
	if (fd < 0)
	{
		parsing_error(MS_ERROR_TO_PERROR);
		return ;
	}
	if (find_next_cmd())
		find_next_cmd()->content->pipe_out = fd;
	else if (find_prev_cmd())
		find_prev_cmd()->content->pipe_out = fd;
	else
	{
		parsing_error(MS_ERROR_NO_CMD);
		return ;
	}
}

void	parse_simple_redirection_left(void)
{
	int	fd;

	fd = -1;
	if (fd > 0)
		close(fd);
	if (is_there_literal_for_file() == False)
		return ;
	fd = open(find_next_literal(1)->content->value, O_RDONLY);
	if (fd < 0)
	{
		parsing_error(MS_ERROR_TO_PERROR);
		return ;
	}
	if (find_next_cmd())
		find_next_cmd()->content->pipe_in = fd;
	else if (find_prev_cmd())
		find_prev_cmd()->content->pipe_in = fd;
	else
	{
		parsing_error(MS_ERROR_NO_CMD);
		return ;
	}
}

void	parse_double_redirection_left(void)
{
	char	*end_redir;
	char	*buffer;
	int		fd[2];

	buffer = NULL;
	if (is_there_literal_for_file() == False)
		return ;
	end_redir = find_next_literal(1)->content->value;
	pipe(fd);
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
		parsing_error(MS_ERROR_NO_CMD);
		return ;
	}
}

void	parse_pipe(void)
{
	int		fd[2];
	t_cmd	*current;
	int		tmp_fd;

	current = g_minishell.list_input;
	if (g_minishell.list_input->prev)
		g_minishell.list_input = g_minishell.list_input->prev;
	else
		return ;
	if (find_prev_cmd()->content->pipe_out == STDOUT_FILENO)
	{
		if (pipe(fd) < 0)
		{
			perror("minishell");
			return ;
		}
		if (find_prev_cmd())
			find_prev_cmd()->content->pipe_out = fd[1];
		else
			return ; // Erreur
		g_minishell.list_input = current->next;
		if (find_next_cmd())
			find_next_cmd()->content->pipe_in = fd[0];
		else
			return ; // Erreur
	}
	else
	{
		tmp_fd = find_prev_cmd()->content->pipe_out;
		g_minishell.list_input = current->next;
		find_next_cmd()->content->pipe_in = tmp_fd;
	}
	g_minishell.list_input = current;
}

/* Erreurs possibles :
** cmd > > file1 : parse error
** cmd > file1 file2 : too many arguments
** cmd1 > cmd2 : Fonctionne (le fichier cmd2 est créé)
**
*/
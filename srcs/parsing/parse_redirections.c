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

void	parse_simple_redirection_right(void)
{
	int	fd;

	fd = -1;
	if (fd > 0)
		close(fd);
	if (is_there_literal_for_file() == False)
		return ;
	fd = open(find_next_literal(1)->content->value,
			O_CREAT | O_RDWR | O_TRUNC, 0666);
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
		return ;
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
			O_CREAT | O_RDWR | O_APPEND, 0666);
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
		return ;
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
		return ;
}

void	parse_double_redirection_left(void)
{
	char	*end_redir;
	char	*buffer;
	int		fd[2];
	pid_t	pid;
	int		retval;

	buffer = NULL;
	if (is_there_literal_for_file() == False)
		return ;
	end_redir = find_next_literal(1)->content->value;
	g_minishell.signal = 1;
	if (pipe(fd) < 0)
		cmd_error();
	if (find_next_cmd())
		find_next_cmd()->content->pipe_in = fd[0];
	else if (find_prev_cmd())
		find_prev_cmd()->content->pipe_in = fd[0];
	else
		return ;
	pid = fork();
	if (pid == -1)
		cmd_error();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (True)
		{
			buffer = readline("\033[1;32m>\033[0m ");
			if (!buffer || !ft_strcmp(buffer, end_redir))
				break ;
			buffer = ft_strjoin_free(buffer, "\n");
			buffer = dollar_to_value(buffer, 0);
			ft_putstr_fd(buffer, fd[1]);
			free(buffer);
		}
		free(buffer);
		close(fd[1]);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &retval, 0);
/* 		read(fd[0], buffer, 256);
		printf("buffer : %s\n", buffer); */
		close(fd[1]);
		if (retval != 0)
		{
			write(STDIN_FILENO, "\n", 1);
			close(fd[0]);
			g_minishell.signal = 0;
		}
	}
}

void	parse_pipe(void)
{
	int		fd[2];
	t_cmd	*current;

	current = g_minishell.list_input;
	if (g_minishell.list_input->prev)
		g_minishell.list_input = g_minishell.list_input->prev;
	else
	{
		parsing_error(MS_ERROR_SYNTAX);
		return ;
	}
	assign_pipe(fd, current);
	g_minishell.list_input = current;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:07:13 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/11/23 17:07:13 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	assign_pipe(int *fd, t_cmd *current, int tmp_fd)
{
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
			return ;
		g_minishell.list_input = current->next;
		if (find_next_cmd())
			find_next_cmd()->content->pipe_in = fd[0];
		else
			return ;
	}
	else
	{
		tmp_fd = find_prev_cmd()->content->pipe_out;
		g_minishell.list_input = current->next;
		find_next_cmd()->content->pipe_in = tmp_fd;
	}
}

void	detect_file_type(void)
{
	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == simple_redir_left
			|| g_minishell.list_input->content->type == double_redir_left
			|| g_minishell.list_input->content->type == simple_redir_right
			|| g_minishell.list_input->content->type == double_redir_right)
		find_next_literal(1)->content->type = filename;
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

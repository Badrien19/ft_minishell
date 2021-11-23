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

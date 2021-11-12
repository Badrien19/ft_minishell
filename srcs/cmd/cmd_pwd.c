/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:49:46 by user42            #+#    #+#             */
/*   Updated: 2021/11/04 16:38:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_pwd(t_cmd *list)
{
	int i;
	int	j;
	pid_t	pid;
	
	pid = fork();
	if (!pid)
	{
		i = 0;
		j = 4;
		while (g_minishell.env[i] && ft_strncmp(g_minishell.env[i], "PWD=", 4))
			i++;
		while (g_minishell.env[i][j])
		{
			write(list->content->pipe_out, &g_minishell.env[i][j], 1);
			j++;
		}
		write(list->content->pipe_out, "\n", 1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if(list->content->pipe_out && list->content->pipe_out != 1)
			close(list->content->pipe_out);
		if(list->content->pipe_in && list->content->pipe_in != 0)
			close(list->content->pipe_in);
		exit(0);
	}
}

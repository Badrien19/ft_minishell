/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:49:46 by user42            #+#    #+#             */
/*   Updated: 2021/11/18 19:47:37 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_pwdchild(t_cmd *list)
{
	int		i;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	while (cwd[i])
	{
		write(list->content->pipe_out, &cwd[i], 1);
		i++;
	}
	write(list->content->pipe_out, "\n", 1);
	free(cwd);
}

void	cmd_pwd(t_cmd *list)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		ft_pwdchild(list);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (list->content->pipe_out && list->content->pipe_out != 1)
			close(list->content->pipe_out);
		if (list->content->pipe_in && list->content->pipe_in != 0)
			close(list->content->pipe_in);
	}
}

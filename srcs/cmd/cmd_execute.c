/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:47:41 by user42            #+#    #+#             */
/*   Updated: 2021/12/02 15:05:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	*get_path_pwd(char **env)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_strdup((env[i] + 4));
			break ;
		}
	}
	return (path);
}

static void	execute_child(t_cmd *list)
{
	char	*path;
	char	**args;
	char	*tmp;

	args = ft_split(list->content->value, '/');
	path = get_path_pwd(g_minishell.env);
	tmp = ft_strjoin(path, "/");
	free(path);
	tmp = ft_strjoin_free(tmp, args[1]);
	execve(tmp, args, g_minishell.env);
	free(tmp);
	free_array(args);
	if (errno)
		g_minishell.last_return_value = errno;
	else
		g_minishell.last_return_value = 0;
	perror("minishell");
}

void	cmd_execute(t_cmd *list)
{
	int		pid;
	int		in;
	int		out;

	pid = fork();
	in = list->content->pipe_in;
	out = list->content->pipe_out;
	if (!pid)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != STDOUT_FILENO)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		execute_child(list);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

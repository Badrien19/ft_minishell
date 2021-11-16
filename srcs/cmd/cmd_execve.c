/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:56:30 by arapaill          #+#    #+#             */
/*   Updated: 2021/11/16 14:09:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	**get_path(char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split((env[i] + 5), ':');
			break ;
		}
	}
	return (path);
}

void	free_array(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
		free (array[i]);
	free(array);
}

void	ft_exec_free(t_cmd *list, char *cmd)
{
	char	**args;
	char	**path;
	char	*tmp;
	size_t	i;

	i = -1;
	if (ft_strlen(cmd) == 0)
		parsing_error(4);
	args = ft_split(cmd, ' ');
	path = get_path(g_minishell.env);
	while (path[++i])
	{
		if (args[0][0] != '/')
		{
			tmp = ft_strjoin(path[i], "/");
			tmp = ft_strjoin_free(tmp, args[0]);
		}
		execve(tmp, args, g_minishell.env);
		free(tmp);
	}
	free_array(args);
	free_array(path);
	parsing_error(4);
}

void	ft_loop_execve(t_cmd *list, int in, int out, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error("minishell: Failed to create a fork\n");
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
		ft_exec_free(list, cmd);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	cmd_execve(t_cmd *list)
{
	int		in;
	int		out;
	char	*cmd;

	cmd = ft_strdup(list->content->value);
	in = list->content->pipe_in;
	out = list->content->pipe_out;
	while (list->next && (list->next->content->type == literal
			|| list->next->content->type == variable
			|| list->next->content->type == single_quote
			|| list->next->content->type == double_quote
			|| list->next->content->type == space))
	{
		cmd = ft_strjoin_free(cmd, list->next->content->value);
		list = list->next;
	}
	ft_loop_execve(list, in, out, cmd);
}

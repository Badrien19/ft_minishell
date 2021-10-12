/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:56:30 by arapaill          #+#    #+#             */
/*   Updated: 2021/10/12 16:13:35 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

char	**get_path(char **env)
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

void	cmd_execve(t_cmd *list)
{
	pid_t	pid;
	char	*cmd;
	int		pipefd[2];


	cmd = ft_strdup(list->content->value);
	while (list->next && (list->next->content->type == literal || list->next->content->type == variable ||
	list->next->content->type == single_quote || list->next->content->type == double_quote || list->next->content->type == space))
	{
		printf("entry_execve -> '%s'\n", (char *)list->next->content->value);
		cmd = ft_strjoin_free(cmd, list->next->content->value);
		list = list->next;
	}
	//printf("TEST %s\n", cmd);
	if (pipe(pipefd) == -1)
		error("minishell: Failed to create a pipe\n");
	pid = fork();
	if (pid == -1)
		error("minishell: Failed to create a fork\n");
	if (!pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], list->content->pipe_in);
		dup2(list->content->pipe_out, list->content->pipe_out);
		ft_exec_free(list, cmd);
	}
	else
	{
		waitpid(pid, NULL, 0);
		exit(0);
	}
}

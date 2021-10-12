/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:56:30 by arapaill          #+#    #+#             */
/*   Updated: 2021/10/12 14:34:07 by arapaill         ###   ########.fr       */
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

void	ft_exec_free(t_cmd *list)
{
	char	**args;
	char	**path;
	char	*tmp;
	size_t	i;

	i = -1;
	if (ft_strlen(list->content->value) == 0)
		parsing_error(4);
	args = ft_split(list->content->value, ' ');
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
	int		pipefd[2];

	printf("entry_execve -> '%s'\n", (char *)list->content->value);
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
		ft_exec_free(list);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

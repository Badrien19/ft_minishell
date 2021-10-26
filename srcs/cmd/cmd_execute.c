/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:47:41 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 15:01:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char **get_path_pwd(char **env)
{
		char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_split((env[i] + 4), ':');
			break ;
		}
	}
	return (path);
	
}

static void execute_child(t_cmd *list)
{
	char	**path;
	char	**args;
	char	*tmp;
	size_t	i;
	
	i = -1;
	args = ft_split(list->content->value, '/');
	path = get_path_pwd(g_minishell.env);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin_free(tmp, args[1]);
		execve(tmp, args, g_minishell.env);
		free(tmp);
	}
	free_array(path);
	perror("minishell");
}

void cmd_execute(t_cmd *list)
{

	int		pid;
	int		in;
	int		out;
	
	pid = fork();
	in = list->content->pipe_in;
	out = list->content->pipe_out;
	if(!pid)
	{
		if(in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if(out != STDOUT_FILENO)
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

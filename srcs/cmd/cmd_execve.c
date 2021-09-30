/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:56:30 by arapaill          #+#    #+#             */
/*   Updated: 2021/09/30 16:44:43 by arapaill         ###   ########.fr       */
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

void	cmd_execve(t_cmd *list)
{
	char	**args;
	char	**path;
	char	*tmp;
	size_t	i;

	i = -1;
	if (ft_strlen(list->content->value) == 0)
		return ;
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
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:03:09 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 17:03:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	check_path(char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;
	char	**paths;

	i = 0;
	while (g_minishell.env[i] != NULL
		&& ft_strnstr(g_minishell.env[i], "PATH=", 5) == 0)
		i++;
	if (g_minishell.env[i] != NULL)
		paths = ft_split(g_minishell.env[i] + 5, ':');
	else
		return (False);
	i = 0;
	while (paths[i])
	{
		if (cmd[0] != '/')
		{
			tmp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(tmp, cmd);
			free(tmp);
		}
		if (access(path, X_OK) == 0)
		{
			free(path);
			free_array(paths);
			return (True);
		}
		i++;
		free(path);
	}
	free_array(paths);
	return (False);
}

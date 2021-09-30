/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:50:18 by arapaill          #+#    #+#             */
/*   Updated: 2021/09/30 09:57:21 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int		envchr(char *value)
{
	int		len;
	int		i;
	char	*needle;

	
	len = 0;
	i = -1;
	while (value[len] && value[len] != '=')
		len++;
	needle = malloc(sizeof(char *) * len + 1);
	if(!needle)
		error("Malloc error");
	while (g_minishell.env[++i])
		if(ft_strncmp(needle, g_minishell.env[i], len))
			return(1);
	return(0);
}

void	cmd_export(t_cmd *list)
{
	int	env_size;
	char **tmp;
	int	i;

	i = 0;
	if (!list->next)
		return ;
	list = list->next;
	while (list && list->content->type != semicolon)
	{
		if(ft_strchr((char *)list->content->value, 61))
		{
			env_size = 0;
			while (g_minishell.env[env_size] && envchr((char *)list->content->value))
				env_size++;
			env_size--;
			tmp = g_minishell.env;
			g_minishell.env = realloc_env(env_size + 1);
			copy_env(env_size, tmp);
			g_minishell.env[env_size + 1] = ft_strdup((char *) list->content->value);
		}
		list = list->next;
	}
}
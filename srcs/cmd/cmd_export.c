/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:50:18 by arapaill          #+#    #+#             */
/*   Updated: 2021/12/09 18:23:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_exporting_2(char *value, int s)
{
	if (envchr(value, -1) == -1)
	{
		if (ft_envplussearch(value) != 0)
			value = ft_plus_cut(value);
		s = size_env(g_minishell.env);
		g_minishell.env = realloc_env(g_minishell.env, s + 1);
		g_minishell.env[s] = ft_strdup(value);
		free(value);
		if (!g_minishell.env[s])
			cmd_error();
		g_minishell.env[s + 1] = NULL;
	}
	else if (envchr(value, -1) > -1)
	{
		s = envchr(value, -1);
		free(g_minishell.env[s]);
		g_minishell.env[s] = ft_strdup(value);
		free(value);
		if (!g_minishell.env[s])
			cmd_error();
	}
}

void	ft_exporting(t_cmd *list, char *value)
{
	int	s;

	while (list && ft_isstop(list))
	{
		if (ft_strchr(value, 61))
		{
			s = 0;
			if (ft_envplussearch(value) != 0 && envchr(value, -1) > -1)
			{
				s = envchr(value, -1);
				g_minishell.env[s] = ft_strjoin_free(g_minishell.env[s],
						&value[ft_envplussearch(value) + 2]);
				free(value);
				if (!g_minishell.env[s])
					cmd_error();
			}
			else
				ft_exporting_2(value, s);
		}
		list = list->next;
	}
}

static void	loop_export(t_cmd *list, char *value)
{
	while (list && ft_isstop(list))
	{
		while (list->next && list->content->type == space)
			list = list->next;
		if (!ft_isstop(list))
			return ;
		if (!ft_isalpha(((char *)list->content->value)[0]))
		{
			printf("minishell: export: %s not a valid identifier\n",
				(char *)list->content->value);
			list = list->next;
			g_minishell.last_return_value = 1;
		}
		if (!ft_isstop(list))
			return ;
		value = ft_strdup(list->content->value);
		if (!value)
			cmd_error();
		ft_exporting(list, value);
		list = list->next;
	}
}

void	cmd_export(t_cmd *list)
{
	char	*value;

	if (!list || list->next == NULL)
		return ;
	list = list->next;
	g_minishell.last_return_value = 0;
	value = NULL;
	loop_export(list, value);
}

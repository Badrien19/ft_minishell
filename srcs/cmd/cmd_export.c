/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:50:18 by arapaill          #+#    #+#             */
/*   Updated: 2021/11/23 17:23:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	envchr(char *value)
{
	int		len;
	int		i;
	char	*needle;

	len = 0;
	i = -1;
	while (value[len] && value[len] != '=')
		len++;
	needle = malloc(sizeof(char *) * len);
	if (!needle)
		error("Malloc error");
	while (++i < len)
		needle[i] = value[i];
	needle[len] = '\0';
	i = -1;
	while (g_minishell.env[++i])
	{
		if (!ft_strncmp(needle, g_minishell.env[i], len))
		{
			free(needle);
			return (i);
		}
	}
	free(needle);
	return (-1);
}

void	ft_exporting(t_cmd *list, char *value)
{
	int	s;

	while (list && ft_isstop(list))
	{
		if (ft_strchr(value, 61))
		{
			s = 0;
			if (envchr(value) == -1)
			{
				s = size_env(g_minishell.env);
				g_minishell.env = realloc_env(g_minishell.env, s + 1);
				g_minishell.env[s]
					= ft_strdup(value);
				g_minishell.env[s + 1] = NULL;
			}
			else
			{
				s = envchr(value);
				free(g_minishell.env[s]);
				g_minishell.env[s] = ft_strdup(value);
			}
		}
		list = list->next;
	}
}

void	cmd_export(t_cmd *list)
{
	char	*value;

	if (!list || list->next == NULL)
		return ;
	list = list->next;
	value = ft_strdup(list->content->value);
	if (list->next && (list->next->content->type == double_quote
			|| list->next->content->type == single_quote))
	{
		value = ft_strjoin_free(value, list->next->content->value);
		list = list->next;
	}
	if (!ft_isalpha(value[0]))
	{
		printf("minishell: export: %s not a valid identifier\n", value);
		g_minishell.last_return_value = 1;
		return ;
	}
	ft_exporting(list, value);
	free(value);
	g_minishell.last_return_value = 0;
}

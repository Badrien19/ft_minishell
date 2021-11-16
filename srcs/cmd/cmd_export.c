/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:50:18 by arapaill          #+#    #+#             */
/*   Updated: 2021/11/16 16:59:48 by user42           ###   ########.fr       */
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
			return (i);
	}
	return (0);
}

static void	ft_exporting(int i, int j, t_cmd *list)
{
	int	s;

	while (list && list->content->type != semicolon)
	{
		if (ft_strchr((char *)list->content->value, 61))
		{
			s = 0;
			if (envchr((char *)list->content->value) == 0)
			{
				while (g_minishell.env[s])
					s++;
				s--;
				g_minishell.env = realloc_env(s + 2);
				g_minishell.env[s + 1]
					= ft_strdup((char *)list->content->value);
				g_minishell.env[s + 2] = NULL;
			}
			else
			{
				s = envchr((char *)list->content->value);
				g_minishell.env[s] = ft_strdup((char *) list->content->value);
			}
		}
		list = list->next;
	}
}

void	cmd_export(t_cmd *list)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (!list || list->next == NULL)
		return ;
	list = list->next;
	if (!ft_isalpha(((char *)list->content->value)[0]))
	{
		printf("minishell: export: %s not a valid identifier\n",
			(char *)list->content->value);
		return ;
	}
	ft_exporting(i, j, list);
}

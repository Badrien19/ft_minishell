/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:50:18 by arapaill          #+#    #+#             */
/*   Updated: 2021/09/30 12:31:08 by arapaill         ###   ########.fr       */
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
	//printf("len %i\n", len);
	needle = malloc(sizeof(char *) * len);
	if(!needle)
		error("Malloc error");
	while (++i < len)
		needle[i] = value[i];
	needle[len] = '\0';
	i = -1;
	while (g_minishell.env[++i])
	{
		//printf("len :%i needle:%s env %s\n", len, needle, g_minishell.env[i]);
		if(!ft_strncmp(needle, g_minishell.env[i], len))
		{
			//printf("i = %i\n", i);
			return(i);
		}
	}
	return(0);
}

void	cmd_export(t_cmd *list)
{
	int	env_size;
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (!list || list->next == NULL)
		return ;
	list = list->next;
	while (list && list->content->type != semicolon)
	{
		if(ft_strchr((char *)list->content->value, 61))
		{
			env_size = 0;
			if (envchr((char *)list->content->value) == 0)
			{
				while (g_minishell.env[env_size])
					env_size++;
				env_size--;
				g_minishell.env = realloc_env(env_size + 2);
				g_minishell.env[env_size + 1] = ft_strdup((char *) list->content->value);
				g_minishell.env[env_size + 2] = NULL;
			}
			else
			{
				env_size = envchr((char *)list->content->value);
				g_minishell.env[env_size] = ft_strdup((char *) list->content->value);
			}
		}
		list = list->next;
	}
}
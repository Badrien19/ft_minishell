/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:46:55 by arapaill          #+#    #+#             */
/*   Updated: 2021/09/28 13:50:43 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minishell.h"

void	copy_env(int env_size, char **tmp)
{
	int		i;

	i = 0;
	while (env_size > i)
	{
		g_minishell.env[i] = tmp[i];
		i++;
	}
	//free(tmp);
}

void    cmd_unset(t_list *list)
{
	int     i;
	int		env_size;
	int		word_size;
	char 	 **tmp;

	i = -1;
	tmp = NULL;
	if (!list->next)
		return ;
	list = list->next;
	while(g_minishell.env[++i])
	{
		env_size = 0;
		while (g_minishell.env[env_size])
			env_size++;
		env_size--;
		word_size = ft_strlen(list->content->value);
		if (!ft_strncmp(list->content->value, g_minishell.env[i], word_size))
		{
			printf("i = %d env_size = %d\n", i, env_size);
			g_minishell.env[i] = g_minishell.env[env_size];
			env_size--;
			tmp = g_minishell.env;
			g_minishell.env = realloc_env(env_size);
			copy_env(env_size, tmp);
			if (!list->next || list->next->content->type == semicolon)
				return ;
			list = list->next;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:46:55 by arapaill          #+#    #+#             */
/*   Updated: 2021/11/04 15:42:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_unseting(t_cmd *list)
{
	int     i;
	int		env_size;
	int		word_size;
	
	i = -1;
	while(g_minishell.env[++i])
		{
			env_size = 0;
			while (g_minishell.env[env_size])
				env_size++;
			env_size--;
			word_size = ft_strlen(list->content->value);
			if (!ft_strncmp(list->content->value, g_minishell.env[i], word_size))
			{
				//printf("i = %d env_size = %d\n", i, env_size);
				g_minishell.env[i] = g_minishell.env[env_size];
				env_size--;
				g_minishell.env = realloc_env(env_size);
				if (!list->next || list->next->content->type == semicolon)
					return ;
				list = list->next;
			}
		}
}

void    cmd_unset(t_cmd *list)
{
	int     i;
	pid_t	pid;
	int		env_size;
	int		word_size;

	if (!list || list->next == NULL)
		return ;
	list = list->next;
	pid = fork();
	if(!pid)
	{
		ft_unseting(list);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:50:18 by arapaill          #+#    #+#             */
/*   Updated: 2021/11/12 09:37:29 by user42           ###   ########.fr       */
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
	needle = malloc(sizeof(char *) * len);
	if(!needle)
		error("Malloc error");
	while (++i < len)
		needle[i] = value[i];
	needle[len] = '\0';
	i = -1;
	while (g_minishell.env[++i])
	{
		if(!ft_strncmp(needle, g_minishell.env[i], len))
			return(i);
	}
	return(0);
}

static void	ft_exporting(int i, int j, t_cmd *list)
{
	int	env_size;
	
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

void	cmd_export(t_cmd *list)
{
	int	i;
	int	pid;
	int	j;

	i = 0;
	j = -1;
	if (!list || list->next == NULL)
		return ;
	list = list->next;
	if (!ft_isalpha(((char *)list->content->value)[0]))
	{
		write(1, "minishell: unset: ", 18);
		write(1, list->content->value, ft_strlen((char *)list->content->value));
		write(1, " not a valid identifier\n", 24);
	}
	pid = fork();
	if (!pid)
	{
		ft_exporting(i, j, list);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
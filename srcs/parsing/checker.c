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
	while (ft_strnstr(g_minishell.env[i], "PATH=", 5) == 0
		&& g_minishell.env[i] != NULL)
		i++;
	if (g_minishell.env[i] != NULL)
		paths = ft_split(g_minishell.env[i] + 5, ':');
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
			return (True);
		i++;
	}
	return (False);
}

t_bool	checking_if_quotes_even(void)
{
	t_cmd	*list;
	int		quote;

	list = g_minishell.list_input;
	quote = 0;
	if (list == NULL)
		error("List is empty.\n");
	while (list && list->next)
	{	
		if(list->content->type == double_quote)
			quote = 1;
		while (quote == 1)
		{
			if(list->next)
				list = list->next;
			else
			{
				printf("Warning: Quotes are uneven.\n");
				return(False);
			}
			if(list->content->type == line_return)
			{
				printf("Warning: Quotes are uneven.\n");
				return(False);
			}
			if(list->content->type == backslash)
			{
				if (list->next && list->next->next)
					list = list->next->next;
				else
				{
					printf("Warning: Quotes are uneven.\n");
					return(False);
				}
				if(list->content->type == line_return)
					quote = 0;
			}
			if(list->content->type == double_quote)
				quote = 0;
		}
		if(list->content->type == single_quote)
			quote = 1;
		while (quote == 1)
		{
			if(list->next)
				list = list->next;
			else
			{
				printf("Warning : Quotes are uneven.\n");
				return(False);
			}
			if(list->content->type == backslash)
			{
				if (list->next && list->next->next)
					list = list->next->next;
				else
				{
					printf("Warning: Quotes are uneven.\n");
					return(False);
				}
				if(list->content->type == line_return)
					quote = 0;
			}
			if(list->content->type == line_return)
			{
				printf("Warning : Quotes are uneven.\n");
				return(False);
			}
			if(list->content->type == single_quote)
				quote = 0;
		}
		if(list->next)
			list = list->next;
		else
			return(True);
		if(list->content->type == line_return)
			return (True);
	}
	return (True);
}

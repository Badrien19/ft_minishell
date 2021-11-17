/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:15:04 by user42            #+#    #+#             */
/*   Updated: 2021/11/17 16:01:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_switch(t_cmd *list)
{
	debug();
	if (list && list->content->type == cmd_instr)
	{
		if (!ft_strcmp(list->content->value, "exit"))
			error("Exiting minishell...\n");
		else if (!ft_strcmp(list->content->value, "echo"))
			cmd_echo(list);
		else if (!ft_strcmp(list->content->value, "env"))
			print_env();
		else if (!ft_strcmp(list->content->value, "pwd"))
			cmd_pwd(list);
		else if (!ft_strcmp(list->content->value, "cd"))
			cmd_cd(list->next->next);
		else if (!ft_strncmp(list->content->value, "./", 2))
			cmd_execute(list);
		else if (!ft_strcmp(list->content->value, "unset"))
			cmd_unset(list->next);
		else if (!ft_strcmp(list->content->value, "export"))
			cmd_export(list->next);
		else
			cmd_execve(list);
	}
	else if (list->content->type == none || list->content->type == semicolon)
		return ;
	else
		perror("minishell");
}

void	cmd_hub(void)
{
	t_cmd	*list;

	list = g_minishell.list_input;
	concat_tokens_same_type();
	detect_cmd_type();
	remove_quote_dollar(list);
	while (list->content->type == space && list->next)
		list = list->next;
	ft_switch(list);
	while (list != NULL)
	{
		if (!ft_isstop(list))
		{
			while (list->next && list->content->type != cmd_instr)
				list = list->next;
			while (list->content->type == space && list->next)
				list = list->next;
			ft_switch(list);
		}
		list = list->next;
	}
}

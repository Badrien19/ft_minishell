/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:15:04 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 14:55:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_switch(t_cmd *list)
{
	//printf("\nentry -> %s\n", list->content->value);
	while(list->content->type == space && list->next)
		list = list->next;
	if (g_minishell.parsing_error == False && list && list->content->type == cmd_instr)
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
	else
		printf("Minishell: %s command not found\n",(char *) list->content->value);
	
	 // Why ? Crash si on fait appel à un commande style "test"
}

void		cmd_hub(void)
{
	t_cmd	*list;
	
	list = g_minishell.list_input;
	remove_quote_dollar(list);
	concat_tokens_same_type();
	detect_cmd_type();
	//debug();
	ft_switch(list);
	while (list != NULL)
	{
		if (list->content->type == semicolon || list->content->type == pipeline) 
		{
			while (list->next && list->content->type != cmd_instr)
				list = list->next;
			//printf("value: %s\n", list->content->value);
			ft_switch(list);
		}
		list = list->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:15:04 by user42            #+#    #+#             */
/*   Updated: 2021/12/03 12:17:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_switch(t_cmd *list)
{
	if (!ft_strcmp(list->content->value, "exit"))
	{
		free_list();
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strcmp(list->content->value, "echo"))
		cmd_echo(list);
	else if (!ft_strcmp(list->content->value, "env"))
		print_env();
	else if (!ft_strcmp(list->content->value, "pwd"))
		cmd_pwd(list);
	else if (!ft_strcmp(list->content->value, "cd"))
		cmd_cd(list->next);
	else if (!ft_strncmp(list->content->value, "./", 2))
		cmd_execute(list);
	else if (!ft_strcmp(list->content->value, "unset"))
		cmd_unset(list->next);
	else if (!ft_strcmp(list->content->value, "export"))
		cmd_export(list->next);
	else
		cmd_execve(list);
}

static void	loop_hub(t_cmd *list)
{
	replace_value_from_env(list);
	concat_tokens_same_type();
	detect_cmd_type();
	detect_file_type();

	if (list && list->content->type == cmd_instr)
		ft_switch(list);
	else if (!ft_isstop(list) || list->content->type == filename)
		return ;
	else if (errno == 2)
		parsing_error(MS_ERROR_NO_CMD);
	else if (errno != 0)
		perror("minishell");
}
void	cmd_hub(void)
{
	t_cmd	*list;

	list = g_minishell.list_input;
	while (list->content->type == space && list->next)
		list = list->next;
	loop_hub(list);
	while (list != NULL)
	{
		if (!ft_isstop(list))
		{
			while (list->content->type == space && list->next)
				list = list->next;
			while (list->next && list->content->type != cmd_instr
				&& list->content->type != literal
				&& list->content->type != filename
				&& list->content->type != variable)
				list = list->next;
			loop_hub(list);
		}
		list = list->next;
	}
}

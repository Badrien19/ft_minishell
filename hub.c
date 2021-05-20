/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:05:31 by user42            #+#    #+#             */
/*   Updated: 2021/05/20 18:49:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	cmd_echo(t_list *list)
{
	int		quote;

	quote = 0;
	while (list && list->content->type != semicolon)
	{
		if(list->content->type == single_quote)
			quote = 1;
			while (quote = 1)
			{
				printf("%s", list->content->value);
				if(list->next)
					list = list->next;
				else
					return ;
				if(list->content->type == semicolon)
					return ;
				if(list->content->type == single_quote)
					quote = 0;
			}
			if(list->content->type == double_quote)
				quote = 1;
			while (quote = 1)
			{
				printf("%s", list->content->value);
				list = list->next;
				if(list->content->type == semicolon)
					return ;
				if(list->content->type == double_quote)
					quote = 0;
			}
			if(list->content->type == semicolon)
				return ;
			if(list->content->type == backslash )
				{
					if(list->next)
						printf("%s", list->next->content->value);
					if(list->next && list->next->next)
						list = list->next->next;
					else
						return ;
				}
			if(list->content->type == semicolon)
				return ;
			printf("%s", list->content->value);
			if(list->next)
					list = list->next;
			else
				return ;
	}
	

}

void	cmd_hub(void)
{
	t_list	*list;

	list = g_sys_infos.list_input;
	while (list)
	{
		if(list->content->type == literal && !ft_strcmp(list->content->value, "exit"))
			error("exit minishell\n");
		if(list->content->type == literal && !ft_strcmp(list->content->value, "echo"))
			cmd_echo(list->next);
		if(list->next)
			list = list->next;
		else
			break ;
	}
	
}
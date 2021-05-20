/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:05:31 by user42            #+#    #+#             */
/*   Updated: 2021/05/20 22:43:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	print_quote(void *s)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while(i < (ft_strlen(str) - 2))
		printf("%c", str[++i]);
}

void	cmd_echo(t_list *list)
{
	int		quote;

	quote = 0;
	while (list && list->content->type != 3)
	{
		if(list->content->type == 9)
			quote = 1;
			if (quote == 1)
			{
				print_quote(list->content->value);
				if(list->next)
					list = list->next;
				else
					return ;
				if(list->content->type == 3 || list->content->type == 1)
					return ;
				quote = 0;
			}
			if(list->content->type == 10)
				quote = 1;
			if (quote == 1)
			{
				print_quote(list->content->value);
				if(list->next)
					list = list->next;
				else
					return ;
				if(list->content->type == 3 || list->content->type == 1)
					return ;
				quote = 0;
			}
			if(list->content->type == 3 || list->content->type == 1)
				return ;

			if(list->content->type == 11 )
				{
					if(list->next)
						printf("%s", list->next->content->value);
					if(list->next && list->next->next)
						list = list->next->next;
					else
						return ;
				}
			if(list->content->type == 3 || list->content->type == 1)
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
			cmd_echo(list->next->next);
		if(list->next)
			list = list->next;
		else
			break ;
	}
	
}
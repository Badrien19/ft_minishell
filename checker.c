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

#include "includes/ft_minishell.h"

t_bool	checking_if_quotes_even(void)
{
	t_list	*list;
	int		quote;

	list = g_sys_infos.list_input;
	quote = 0;
	if (list == NULL)
		error("List is empty.\n");
	while (list && list->next)
	{	
		printf("type : %i value : %s\n", list->content->type, list->content->value);
		if(list->content->type == double_quote)
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
					printf("Warning : Quotes are uneven.\n");
					return(False);
				}
			}
			if(list->content->type == line_return)
			{
				printf("Warning : Quotes are uneven.\n");
				return(False);
			}
			if(list->content->type == double_quote)
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

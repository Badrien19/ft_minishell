/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:05:31 by user42            #+#    #+#             */
/*   Updated: 2021/05/20 18:11:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	cmd_hub(void)
{
	t_list	*list;

	list = g_sys_infos.list_input;
	while (list)
	{
		if(list->content->type == 13 && !ft_strcmp(list->content->value, "exit"))
			error("exit minishell\n");
		if(list->next)
			list = list->next;
		else
			break ;
	}
	
}
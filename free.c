/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:21:04 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 14:51:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minishell.h"

void	free_list(void)
{
	t_list	*buffer;

	if (g_sys_infos.list_input == NULL)
		return ;
	buffer = g_sys_infos.list_input;
	while (buffer != NULL)
	{
		g_sys_infos.list_input = buffer;
		buffer = buffer->next;
		free(g_sys_infos.list_input->content->value);
		free(g_sys_infos.list_input->content);
		free(g_sys_infos.list_input);
	}
	g_sys_infos.list_input = NULL;
}
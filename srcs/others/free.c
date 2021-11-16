/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:21:04 by user42            #+#    #+#             */
/*   Updated: 2021/11/16 16:38:26 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	free_list(void)
{
	t_cmd	*buffer;

	if (g_minishell.list_input == NULL)
		return ;
	buffer = g_minishell.list_input;
	while (buffer != NULL)
	{
		g_minishell.list_input = buffer;
		buffer = buffer->next;
		free(g_minishell.list_input->content->value);
		free(g_minishell.list_input->content);
		free(g_minishell.list_input);
	}
	g_minishell.list_input = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:21:04 by user42            #+#    #+#             */
/*   Updated: 2021/11/22 18:53:46 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	free_list(void)
{
	t_cmd	*buffer;

	if (g_minishell.list_input == NULL)
	{
		free_array(g_minishell.env);
		g_minishell.env = NULL;
		return ;
	}
	buffer = ft_cmdfirst(g_minishell.list_input);
	while (buffer != NULL)
	{
		g_minishell.list_input = buffer;
		buffer = buffer->next;
		free(g_minishell.list_input->content->value);
		g_minishell.list_input->content->value = NULL;
		free(g_minishell.list_input->content);
		g_minishell.list_input->content = NULL;
		free(g_minishell.list_input);
		g_minishell.list_input = NULL;
	}
	free_array(g_minishell.env);
	g_minishell.list_input = NULL;
	g_minishell.env = NULL;
}

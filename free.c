/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:21:04 by user42            #+#    #+#             */
/*   Updated: 2021/05/17 14:59:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	free_cmd(t_cmd	*cmd)
{
	if (cmd->redirect != NULL)
		free(cmd->redirect);
	if (cmd->in != NULL)
		free(cmd->in);
	if (cmd->out != NULL)
		free(cmd->out);
}

void	cmdclear(t_cmd **cmd)
{
	t_cmd	*buffer;

	if (cmd == NULL)
		return ;
	buffer = cmd;
	while (buffer != NULL)
	{
		*cmd = buffer;
		buffer = buffer->out;
		free_cmd(&cmd);
		
	free_cmd(&cmd);
}
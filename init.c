/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:49:45 by user42            #+#    #+#             */
/*   Updated: 2021/05/17 14:15:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void    init_struct_cmd(t_cmd *cmd)
{
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->result = NULL;
    cmd->redirect = malloc(sizeof(t_rdir));
    if(cmd->redirect == NULL)
        return (0);
    cmd->in = malloc(sizeof(t_cmd));
	if (cmd->in == NULL)
		return (0);
    cmd->out = malloc(sizeof(t_cmd));
	if (cmd->out == NULL)
		return (0);
}
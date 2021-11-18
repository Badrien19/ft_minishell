/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/11/18 18:52:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_cd(t_cmd *list)
{
	char	*buffer;

	errno = 0;
	buffer = NULL;
	while (list && list->content->type == space && list->next)
		list = list->next;
	printf("TEST1\n");
	if(!list || !ft_isstop(list) || get_token_value(list->content)[0] == '~')
	{
		chdir(&g_minishell.env[envchr("HOME")][5]);
		g_minishell.env[envchr("PWD")] = ft_strjoin("PWD=", getcwd(buffer, 0));
	}
	else
	{
		chdir(list->content->value);
		g_minishell.env[envchr("PWD")] = ft_strjoin("PWD=", getcwd(buffer, 0));
	}
}

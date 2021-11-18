/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/11/18 22:35:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_cd(t_cmd *list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	while (list && list->content->type == space && list->next)
		list = list->next;
	if (!list || !ft_isstop(list) || get_token_value(list->content)[0] == '~')
		chdir(&g_minishell.env[envchr("HOME")][5]);
	else
		chdir(list->content->value);
	if (envchr("PWD") == -1)
		ft_exporting(list, ft_strjoin("PWD=", cwd));
	else
		g_minishell.env[envchr("PWD")] = ft_strjoin("PWD=", cwd);
	free(cwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/11/23 17:24:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_cd(t_cmd *list)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	if (!tmp)
		error("Malloc error");
	while (list && list->content->type == space && list->next)
		list = list->next;
	if (!list || !ft_isstop(list) || get_token_value(list->content)[0] == '~')
		chdir(&g_minishell.env[envchr("HOME")][5]);
	else
		chdir(list->content->value);
	if (envchr("PWD") == -1)
		ft_exporting(list, tmp);
	else
		g_minishell.env[envchr("PWD")] = tmp;
	free(cwd);
}

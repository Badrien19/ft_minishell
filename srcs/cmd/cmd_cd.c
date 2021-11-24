/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/11/23 18:19:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_cd(t_cmd *list)
{
	char	*cwd;
	char	*tmp;
	int		env_i;

	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	env_i = envchr("PWD=");
	if (!tmp)
		error("Malloc error");
	while (list && list->content->type == space && list->next)
		list = list->next;
	if (!list || !ft_isstop(list) || get_token_value(list->content)[0] == '~')
		chdir(&g_minishell.env[envchr("HOME=")][5]);
	else
		chdir(list->content->value);
	if (env_i == -1)
		ft_exporting(list, tmp);
	else
	{
		free(g_minishell.env[env_i]);
		g_minishell.env[env_i] = tmp;
	}
	free(cwd);
}

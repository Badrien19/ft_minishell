/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/11/24 17:35:30 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_cd(t_cmd *list)
{
	char	*cwd;
	char	*tmp;
	int		env_i;
	int		ret;

	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	env_i = envchr("PWD=");
	if (!tmp)
		error("Malloc error");
	while (list && list->content->type == space && list->next)
		list = list->next;
	if (!list || !ft_isstop(list) || get_token_value(list->content)[0] == '~')
		ret = chdir(&g_minishell.env[envchr("HOME=")][5]);
	else
		ret = chdir(list->content->value);
	if (env_i == -1)
		ft_exporting(list, tmp);
	else
	{
		free(g_minishell.env[env_i]);
		g_minishell.env[env_i] = tmp;
	}
	if (ret < 0)
	{
		g_minishell.last_return_value = 1;
		perror("minishell: cd:");
	}
	else
		g_minishell.last_return_value = 0;
	free(cwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/12/07 16:19:06 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	*get_new_cwd(void)
{
	char	*cwd;
	char	*new_cwd;

	cwd = getcwd(NULL, 0);
	new_cwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	cwd = NULL;
	if (!new_cwd)
		cmd_error();
	return (new_cwd);
}

static t_cmd	*skip_spaces(t_cmd *list)
{
	while (list && list->content->type == space && list->next)
		list = list->next;
	return (list);
}

void	cmd_cd(t_cmd *list)
{
	char	*new_cwd;
	int		env_i;
	int		ret;

	env_i = envchr("PWD=");
	new_cwd = get_new_cwd();
	list = skip_spaces(list);
	if (!list || !ft_isstop(list) || get_token_value(list->content)[0] == '~')
		ret = chdir(&g_minishell.env[envchr("HOME=")][5]);
	else
		ret = chdir(list->content->value);
	if (env_i == -1)
		ft_exporting(list, new_cwd);
	else
	{
		free(g_minishell.env[env_i]);
		g_minishell.env[env_i] = ft_strdup(new_cwd);
	}
	g_minishell.last_return_value = 0;
	if (ret < 0)
	{
		g_minishell.last_return_value = errno;
		perror("minishell: cd");
	}
	free (new_cwd);
}

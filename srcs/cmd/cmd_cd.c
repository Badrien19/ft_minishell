/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/11/18 19:20:41 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_cd(t_cmd *list)
{
	while (list && list->content->type == space && list->next)
		list = list->next;
	if(!list || !ft_isstop(list) || get_token_value(list->content)[0] == '~')
		chdir(&g_minishell.env[envchr("HOME")][5]);
	else
		chdir(list->content->value);
	if (envchr("PWD") == -1)
		ft_exporting(list, ft_strjoin("PWD=", getcwd(NULL, 0)));
	else
		g_minishell.env[envchr("PWD")] = ft_strjoin("PWD=", getcwd(NULL, 0));
}

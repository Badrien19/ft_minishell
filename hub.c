/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:05:31 by user42            #+#    #+#             */
/*   Updated: 2021/05/17 17:42:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	if (s1[0] == '\0' || s2[0] == '\0')
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	cmd_echo(t_list *lst)
{
	
}

void    cmd_check(t_list *lst)
{
	while (lst->next)
	{
		if (ft_strncmp((char *)lst->value, "echo", 4) == 0)
			cmd_echo(lst);
		else if (ft_strncmp((char *)lst->value, "env", 3) == 0)
			cmd_env(lst);
		else if (ft_strncmp((char *)lst->value, "cd", 2) == 0)
			cmd_cd(lst);
		else if (ft_strncmp((char *)lst->value, "pwd", 3) == 0)
			cmd_pwd(lst);
		else if (ft_strncmp((char *)lst->value, "export", 6) == 0)
			cmd_export(lst);
		else if (ft_strncmp((char *)lst->value, "unset", 5) == 0)
			cmd_unset(lst);
		else if (ft_strncmp((char *)lst->value, "exit", 5) == 0)
			exit ;
		else
			no_cmd(lst);
		lst = lst->next;
	}
}
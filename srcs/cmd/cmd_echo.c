/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:58:01 by arapaill          #+#    #+#             */
/*   Updated: 2021/10/07 17:50:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	print_non_quote(void *s)
{
	char	*str;
	int		len;
	int		i;

	str = (char *)s;
	len = ft_strlen(str);
	i = -1;
	while (str[++i] && i < len)
	{
		if (str[i] == '\\')
			i++;
		write(1, &str[i], 1);
	}
}

void	cmd_echo(t_cmd *list)
{
	int		quote;
	int		flag;
	
	//printf("entry_echo -> '%s'\n", list->content->value);
	flag = 0;
	if(list->next && list->content->type == space)
		list = list->next;
	if (list->content->type == literal && !ft_strcmp(list->content->value, "-n"))
	{
		flag = 1;
		if(list->next && list->next->next)
			list = list->next->next;
		else
			return ;
	}
	while (list->content->value && list->content->type != semicolon)
	{
		print_non_quote(list->content->value);
			if (list->next)
				list = list->next;
			else
				break ;
		if (list->content->type == semicolon || list->content->type == line_return)
			break ;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

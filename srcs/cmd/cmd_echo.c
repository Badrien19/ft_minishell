/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:58:01 by arapaill          #+#    #+#             */
/*   Updated: 2021/10/12 15:58:13 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	print_non_quote(void *s, t_cmd *list)
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
		write(list->content->pipe_out, &str[i], 1);
	}
}

void	cmd_echo(t_cmd *list)
{
	int		flag;
	pid_t	pid;
	
	//printf("entry_echo -> '%s'\n", list->content->value);
	pid = fork();
	if(!pid)
	{
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
		while (list->content->value && list->content->type != semicolon &&
		list->content->type != simple_redir_left && list->content->type != simple_redir_right &&
		list->content->type != pipeline)
		{
			print_non_quote(list->content->value, list);
				if (list->next)
					list = list->next;
				else
					break ;
			if (list->content->type == semicolon || list->content->type == line_return)
				break ;
		}
		if (flag == 0)
			write(list->content->pipe_out, "\n", 1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if(list->content->pipe_out && list->content->pipe_out !=1)
			close(list->content->pipe_out);
		if(list->content->pipe_in && list->content->pipe_in !=1)
			close(list->content->pipe_in);
	}
	
}

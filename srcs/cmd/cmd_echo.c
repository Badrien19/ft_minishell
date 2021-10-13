/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:58:01 by arapaill          #+#    #+#             */
/*   Updated: 2021/10/13 09:48:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	print_non_quote(void *s, t_cmd *list, int out)
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
		write(out, &str[i], 1);
	}
}

void	cmd_echo(t_cmd *list)
{
	int		flag;
	int		out;
	pid_t	pid;
	
	pid = fork();
	out = list->content->pipe_out;
	if(list->next)
		list = list->next;
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
		printf("TEST enstry : %d\n", list->content->type);
		while (list->content->value && list->content->type != semicolon &&
		list->content->type != simple_redir_left && list->content->type != simple_redir_right &&
		list->content->type != pipeline && list->content->type != double_redir_left &&
		list->content->type != double_redir_right)
		{
			print_non_quote(list->content->value, list, out);
				if (list->next)
					list = list->next;
				else
					break ;
			if (list->content->type == semicolon || list->content->type == line_return)
				break ;
		}
		if (flag == 0)
			write(out, "\n", 1);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if(list->content->pipe_out && list->content->pipe_out != 1)
			close(list->content->pipe_out);
		if(list->content->pipe_in && list->content->pipe_in != 0)
			close(list->content->pipe_in);
	}
	
}

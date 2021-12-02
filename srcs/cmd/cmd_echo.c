/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:58:01 by arapaill          #+#    #+#             */
/*   Updated: 2021/12/02 18:19:32 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	print_non_quote(void *s, int out)
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
/*
static int	check_space(t_cmd *list)
{
	while (list->next && list->content->type == space)
		list = list->next;
	if (!ft_isstop(list))
		return (0);
	else
		return (1);
}
*/
static void	loop_echo(int flag, t_cmd *list, int out)
{
	while (list->content->type != semicolon
			|| list->content->type != line_return)
	{
		if(list->content->type == literal)
			print_non_quote(list->content->value, out);
		if (list->next)
			list = list->next;
		else
			break ;
		while (list->next && list->content->type == space)
			list = list->next;
		if (list->content->type == semicolon
			|| list->content->type == line_return)
			break ;
		if(list && !ft_isstop(list))
			write(out, " ", 1);
	}
	if (flag == 0)
		write(out, "\n", 1);
}

int	is_flag(t_cmd **list)
{
	int		i;
	int		flag;

	flag = 0;
	while ((*list)->content->type == space && (*list)->next)
		*list = (*list)->next;
	while (!ft_strncmp((*list)->content->value, "-n", 2))
	{
		i = 1;
		while (((char *)(*list)->content->value)[i])
		{
			if (((char *)(*list)->content->value)[i] != 'n')
				return (flag);
			i++;
		}
		flag = 1;
		*list = (*list)->next;
		while ((*list)->content->type == space && (*list)->next)
			*list = (*list)->next;
	}
	return (flag);
}

void	cmd_echo(t_cmd *list)
{
	int		flag;
	int		out;
	pid_t	pid;

	pid = fork();
	out = list->content->pipe_out;
	if (list->next)
		list = list->next;
	while (list->next && list->content->type == space)
		list = list->next;
	if (!pid)
	{
		flag = is_flag(&list);
		loop_echo(flag, list, out);
		exit(EXIT_SUCCESS);
	}
	else
	{
		while (list->content->type != cmd_instr)
			list = list->prev;
		waitpid(pid, NULL, 0);
		if (list->content->pipe_out != STDOUT_FILENO)
			close(list->content->pipe_out);
		if (list->content->pipe_in != STDIN_FILENO)
			close(list->content->pipe_in);
	}
	g_minishell.last_return_value = 0;
}

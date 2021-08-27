/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:05:31 by user42            #+#    #+#             */
/*   Updated: 2021/08/27 09:59:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minishell.h"

static void	print_non_quote(void *s, int flag)
{
	char	*str;
	int		len;
	int		i;

	str = (char *)s;
	len = ft_strlen(str);
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '\\')
			i++;
		write(1, &str[i], 1);
		//printf("%c", str[i]);
		i++;
	}
	if(flag == 0)
		printf("\n");
}

static void	print_double_quote(void *s, int flag)
{
	char	*str;
	int		len;
	int		i;

	str = (char *)s;
	len = ft_strlen(str) - 1;
	i = 1;
	while (str[i] && i < len)
	{
		if (str[i] == '\\')
			i++;
		write(1, &str[i], 1);
		i++;
	}
	if(flag == 0)
		printf("\n");
}

static void	print_single_quote(void *s, int flag)
{
		char	*str;
	int		len;
	int		i;

	str = (char *)s;
	len = ft_strlen(str) - 1;
	i = 1;
	while (str[i] && i < len)
	{
		write(1, &str[i], 1);
		i++;
	}
	if(flag == 0)
		printf("\n");
}

void	cmd_pwd(t_list *list)
{
	int i;
	int	j;

    i = 0;
	j = 4;
	while (g_sys_infos.env[i] && ft_strncmp(g_sys_infos.env[i], "PWD=", 4))
		i++;
	while (g_sys_infos.env[i][j])
	{
		write(1, &g_sys_infos.env[i][j], 1);
		j++;
	}
	write(1, "\n", 1);
}

void	cmd_echo(t_list *list)
{
	int		quote;
	int		flag;
	
	//printf("entry_echo -> '%s'\n", list->content->value);
	quote = 0;
	flag = 0;
	while (list && list->content->type != semicolon)
	{
		if (list->content->type == literal && !ft_strcmp(list->content->value, "-n"))
		{
			flag = 1;
			list = list->next->next;
		}
		if (list->content->type == single_quote)
			quote = 1;
		if (quote == 1)
		{
			print_single_quote(list->content->value, flag);
			if (list->next)
				list = list->next;
			else
				return ;
			if (list->content->type == semicolon || list->content->type == line_return)
				return ;
			quote = 0;
		}
		if (list->content->type == double_quote)
			quote = 1;
		if (quote == 1)
		{
			print_double_quote(list->content->value, flag);
			if (list->next)
				list = list->next;
			else
				return ;
			if (list->content->type == semicolon || list->content->type == line_return)
				return ;
			quote = 0;
		}
		if (list->content->type == semicolon || list->content->type == line_return)
			return ;
		if (list->content->type == backslash)
		{
			if (ft_strcmp(list->content->value, "\\"))
			{
				printf("\\");
				if (list->next)
					list = list->next;
				else
					return ;
			}
			else if (list->next)
			{
				printf("%s\n", (char *)list->next->content->value);
				if (list->next->next)
					list = list->next->next;
				else
					return ;
			}
		}
		if (list->content->type == semicolon || list->content->type == line_return)
			return ;
		if (list->content->type == literal)
			print_non_quote(list->content->value, flag);
		if (list->next)
			list = list->next;
		else
			return ;
	}
}

void	ft_switch(t_list *list)
{
	//printf("\nentry -> %s\n", list->content->value);
	if (list->content->type == literal && !ft_strcmp(list->content->value, "exit"))
		error("exit minishell\n");
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "echo"))
		cmd_echo(list->next->next);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "env"))
		print_env(list->next->next);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "pwd"))
		cmd_pwd(list->next->next);
	else
		{
			printf("%s: command not found\n", (char *) list->content->value);
			error("");
		}
	while (list)
	{
		//printf("value: %s\n", list->content->value);
		if (list->content->type == semicolon && !ft_strcmp(list->content->value, ";"))
		{
			while (list->next && list->content->type != literal)
				list = list->next;
			ft_switch(list);
		}
		if (list->next == NULL)
			break ;
		list = list->next;
	}
}

void	cmd_hub(void)
{
	t_list	*list;

	list = g_sys_infos.list_input;
	ft_switch(list);
}

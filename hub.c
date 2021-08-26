/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:05:31 by user42            #+#    #+#             */
/*   Updated: 2021/08/26 18:25:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minishell.h"

static void	print_non_quote(void *s)
{
	char	*str;
	int		len;
	int		i;

	str = (char *)s;
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == '\\')
			i++;
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
}

static void	print_quote(void *s)
{
	char	*str;
	int		len;
	int		i;

	str = (char *)s;
	len = ft_strlen(str) - 1;
	i = 1;
	while (i < len)
	{
		if (str[i] == '\\')
			i++;
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
}

void	cmd_echo(t_list *list)
{
	int		quote;

	quote = 0;
	printf("entry echo\n");
	while (list && list->content->type != 3)
	{
		if (list->content->type == literal && !ft_strcmp(list->content->value, "-n"))
		{
			printf("\n");
			list = list->next->next;
		}
		if (list->content->type == 9)
			quote = 1;
		if (quote == 1)
		{
			print_quote(list->content->value);
			if (list->next)
				list = list->next;
			else
				return ;
			if (list->content->type == 3 || list->content->type == 1)
				return ;
			quote = 0;
		}
		if (list->content->type == 10)
			quote = 1;
		if (quote == 1)
		{
			print_quote(list->content->value);
			if (list->next)
				list = list->next;
			else
				return ;
			if (list->content->type == 3 || list->content->type == 1)
				return ;
			quote = 0;
		}
		if (list->content->type == 3 || list->content->type == 1)
			return ;
		if (list->content->type == 11 )
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
		if (list->content->type == 3 || list->content->type == 1)
			return ;
		if (list->content->type == literal)
			print_non_quote(list->content->value);
		if (list->next)
			list = list->next;
		else
			return ;
	}
}

void	ft_switch(t_list *list)
{
	if (list->content->type == literal && !ft_strcmp(list->content->value, "exit"))
		error("exit minishell\n");
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "echo"))
		cmd_echo(list->next->next);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "env"))
		print_env(list->next->next);
	else
		{
			printf("%s: command not found\n", (char *) list->content->value);
			error("");
		}
	while (list)
	{
		list = list->next;
		//printf("value: %s\n", list->content->value);
		
		if (list->content->type == semicolon && !ft_strcmp(list->content->value, ";"))
		{
			while (list->next && list->content->type != literal)
				list = list->next;
			ft_switch(list);
		}
		if (list->next == NULL)
			break ;
	}
}

void	cmd_hub(void)
{
	t_list	*list;

	list = g_sys_infos.list_input;
	ft_switch(list);
}

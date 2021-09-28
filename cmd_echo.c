/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:58:01 by arapaill          #+#    #+#             */
/*   Updated: 2021/09/28 13:59:50 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minishell.h"



char	*search_env(char *array, int len)
{
	int		i;
	int		j;
	int		k;
	char	*needle;
	char	*ret;

    i = 0;
	j = len;
	k = -1;
	needle = malloc(sizeof(char *) * len);
	if(!needle)
		error("MALLOC ERROR");
	while (array[i] && array[i] != '$')
		i++;
	i++;
	while (++k < len)
		needle[k] = array[i++];
	needle[k] = '\0';
	k = 0;
	i = 0;
	while (g_minishell.env[i] && ft_strncmp(g_minishell.env[i], needle, len))
		i++;
	if(!g_minishell.env[i])
		return(NULL);
	ret = ft_strdup(g_minishell.env[i]);
	free (needle);
	return (ret);
}

static void	print_non_quote(void *s)
{
	char	*str;
	char	*dollar;
	int		len;
	int		i;
	int		j;

	str = (char *)s;
	len = ft_strlen(str);
	i = -1;
	j = 0;
	while (str[++i] && i < len)
	{
		if (str[i] == '$')
		{
			while (str[i] && str[i++] != ' ')
				j++;
			dollar = search_env(str, j - 1);
			if(dollar)
			{
				dollar = ft_split(dollar, '=')[1];
				if(dollar)
					write(1, dollar, ft_strlen(dollar));
			}
		}
		if (str[i] == '\\')
			i++;
		write(1, &str[i], 1);
	}
}

static void	print_double_quote(void *s)
{
	char	*str;
	char	*dollar;
	int		len;
	int		i;
	int		j;

	str = (char *)s;
	len = ft_strlen(str) - 1;
	i = 1;
	j = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '$')
		{
			while (str[i] && str[i++] != ' ')
				j++;
			dollar = search_env(str, j - 1);
			if(dollar)
			{
				dollar = ft_split(dollar, '=')[1];
				if(dollar)
					write(1, dollar, ft_strlen(dollar));
			}
		}
		if (str[i] == '\\')
			i++;
		write(1, &str[i], 1);
		i++;
	}
}

static void	print_single_quote(void *s)
{
	char	*str;
	char	*dollar;
	int		len;
	int		i;
	int		j;

	str = (char *)s;
	len = ft_strlen(str) - 1;
	i = 1;
	j = 0;
	while (str[i] && i < len)
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	cmd_echo(t_list *list)
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
		if (list->content->type == single_quote)
		{
			print_single_quote(list->content->value);
			if (list->next)
				list = list->next;
			else
				break ;
			if (list->content->type == semicolon || list->content->type == line_return)
				break ;
		}
		else if (list->content->type == double_quote)
		{
			print_double_quote(list->content->value);
			if (list->next)
				list = list->next;
			else
				break ;
			if (list->content->type == semicolon || list->content->type == line_return)
				break ;
		}
		else
		{
			print_non_quote(list->content->value);
			if (list->next)
				list = list->next;
			else
				break ;
		}
		if (list->content->type == semicolon || list->content->type == line_return)
			break ;
		if (list->content->type == backslash)
		{
			if (ft_strcmp(list->content->value, "\\"))
			{
				printf("\\");
				if (list->next)
					list = list->next;
				else
					break ;
			}
			else if (list->next)
			{
				printf("%s\n", (char *)list->next->content->value);
				if (list->next->next)
					list = list->next->next;
				else
					break ;
			}
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
}

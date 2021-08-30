/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walker <walker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:05:31 by user42            #+#    #+#             */
/*   Updated: 2021/08/30 14:53:22 by walker           ###   ########.fr       */
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
	while (++k < len -1)
		needle[k] = array[k];
	needle[k] = '\0';
	k = 0;
	i = 0;
	while (g_minishell.env[i] && ft_strncmp(g_minishell.env[i], needle, len))
		i++;
	ret = malloc(sizeof(char *) * ft_strlen(g_minishell.env[i]) - len);
	if(!ret)
		error("MALLOC ERROR");
	while (g_minishell.env[i][j])
	{
		ret[k] = g_minishell.env[i][j];
		j++;
		k++;
	}
	ret[k] = '\0';
	free (needle);
	return (ret);
}

static void	print_non_quote(void *s, int flag)
{
	char	*str;
	char	*dollar;
	int		len;
	int		i;
	int		j;

	str = (char *)s;
	len = ft_strlen(str);
	i = 0;
	j = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '$')
		{
			while (str[i] != ' ')
				j++;
			dollar = search_env((char *)s, j);
			write(1, &dollar, j - 1);
		}
		if (str[i] == '\\')
			i++;
		write(1, &str[i], 1);
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

void	cmd_pwd(t_node *list)
{
	int i;
	int	j;

    i = 0;
	j = 4;
	while (g_minishell.env[i] && ft_strncmp(g_minishell.env[i], "PWD=", 4))
		i++;
	while (g_minishell.env[i][j])
	{
		write(1, &g_minishell.env[i][j], 1);
		j++;
	}
	write(1, "\n", 1);
}

void	cmd_echo(t_node *list)
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

void	cmd_cd(t_node *list)
{
	int ret;
	char *cwd;

	errno = 0;
	ret = chdir(list->content->value);
	if (ret == -1)
		printf("%s : %s\n", (char*)list->content->value, strerror(errno));
	else
	{
		printf("Successfuly changed directory.\n"); // Temporaire
		add_env("PWD", getcwd(cwd, NULL)); // Il faudrait remplacer la valeur, pas l'ajouter
		if (errno == ERANGE)
			printf("<error> : %s\n", strerror(errno));
		else
			free(cwd);
	}
}


void	ft_switch(t_node *list)
{
	//printf("\nentry -> %s\n", list->content->value);
	if (list->content->type == literal && !ft_strcmp(list->content->value, "exit"))
		error("exit g_minishell\n");
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "echo"))
		cmd_echo(list->next->next);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "env"))
		print_env(list->next->next);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "pwd"))
		cmd_pwd(list->next->next);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "cd"))
		cmd_cd(list->next->next);
/* 	else if (list->content->type == literal && !ft_strcmp(list->content->value, "history"))
	{
		int i = 0;
		HIST_ENTRY **history = history_list();
		while (history[i])
		{
			printf("%s\n", history[i]->line);
			i++;
		}
	} */
	else
		{
			printf("%s : Command not found.\n", (char *) list->content->value);
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
	t_node	*list;

	list = g_minishell.list_input;
	ft_switch(list);
}

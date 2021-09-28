/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:15:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/28 15:49:43 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/ft_minishell.h"

void	cmd_pwd(t_list *list)
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

void	cmd_cd(t_list *list)
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
		//add_env("PWD", getcwd(cwd, NULL)); // Il faudrait remplacer la valeur, pas l'ajouter
		if (errno == ERANGE)
			printf("<error> : %s\n", strerror(errno));
		//else
			//free(cwd);
	}
}

void	cmd_execute(t_list *list)
{
	char *program_name;
	char **argv;

	argv = NULL;

	printf("__TEST__\n");
	program_name = ft_split(list->content->value, '/')[1];
	printf("program_name : %s\n", program_name);
	if (execve(program_name, argv, 0) == -1)
		printf("<Error> : %s\n", strerror(errno));
}

void	ft_switch(t_list *list)
{
	//printf("\nentry -> %s\n", list->content->value);
	if (list->content->type == literal && !ft_strcmp(list->content->value, "exit"))
		error("exit g_minishell\n");
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "echo"))
		cmd_echo(list->next);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "env"))
		print_env(list);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "pwd"))
		cmd_pwd(list);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "cd"))
		cmd_cd(list->next->next);
	else if (list->content->type == literal && !ft_strncmp(list->content->value, "./", 2))
		cmd_execute(list);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "unset"))
		cmd_unset(list->next);
	else if (list->content->type == literal && !ft_strcmp(list->content->value, "export"))
		cmd_export(list->next);
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
		return ;
	}
	while (list)
	{
		//printf("value: %s\n", list->content->value);
		if (list->content->type == semicolon && !ft_strcmp(list->content->value, ";"))
		{
			while (list->next && list->content->type != literal)
				list = list->next;
			if (!list->next)
				return ;
			ft_switch(list);
		}
		list = list->next;
	}
}

void	cmd_hub(void)
{
	t_list	*list;
	list = g_minishell.list_input;
	ft_switch(list);
}

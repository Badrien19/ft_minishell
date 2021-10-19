/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:15:04 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 14:27:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/ft_minishell.h"

void	cmd_pwd(t_cmd *list)
{
	int i;
	int	j;
	pid_t	pid;
	
	pid = fork();
	if (!pid)
	{
		i = 0;
		j = 4;
		while (g_minishell.env[i] && ft_strncmp(g_minishell.env[i], "PWD=", 4))
			i++;
		while (g_minishell.env[i][j])
		{
			write(list->content->pipe_out, &g_minishell.env[i][j], 1);
			j++;
		}
		write(list->content->pipe_out, "\n", 1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if(list->content->pipe_out && list->content->pipe_out != 1)
			close(list->content->pipe_out);
		if(list->content->pipe_in && list->content->pipe_in != 0)
			close(list->content->pipe_in);
		exit(0);
	}
}

void	cmd_cd(t_cmd *list)
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

static char	**get_path_pwd(char **env)
{
		char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_split((env[i] + 4), ':');
			break ;
		}
	}
	return (path);
	
}

void	execute_child(t_cmd *list)
{
	char	**path;
	char	**args;
	char	*tmp;
	size_t	i;
	
	i = -1;
	args = ft_split(list->content->value, '/');
	path = get_path_pwd(g_minishell.env);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin_free(tmp, args[1]);
		execve(tmp, args, g_minishell.env);
		free(tmp);
	}
	free_array(path);
	perror("minishell");
}

void	cmd_execute(t_cmd *list)
{

	int		pid;
	int		in;
	int		out;
	
	pid = fork();
	in = list->content->pipe_in;
	out = list->content->pipe_out;
	if(!pid)
	{
		if(in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if(out != STDOUT_FILENO)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		execute_child(list);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_switch(t_cmd *list)
{
	//printf("\nentry -> %s\n", list->content->value);
	while(list->content->type == space && list->next)
		list = list->next;
	if (g_minishell.parsing_error == False && list && list->content->type == cmd_instr)
	{
		if (!ft_strcmp(list->content->value, "exit"))
			error("Exiting minishell...\n");
		else if (!ft_strcmp(list->content->value, "echo"))
			cmd_echo(list);
		else if (!ft_strcmp(list->content->value, "env"))
			print_env(list);
		else if (!ft_strcmp(list->content->value, "pwd"))
			cmd_pwd(list);
		else if (!ft_strcmp(list->content->value, "cd"))
			cmd_cd(list->next->next);
		else if (!ft_strncmp(list->content->value, "./", 2))
			cmd_execute(list);
		else if (!ft_strcmp(list->content->value, "unset"))
			cmd_unset(list->next);
		else if (!ft_strcmp(list->content->value, "export"))
			cmd_export(list->next);
		else
			cmd_execve(list);
	}
	else
		printf("Minishell: %s command not found\n",(char *) list->content->value);
	
	 // Why ? Crash si on fait appel à un commande style "test"
}

void		cmd_hub(void)
{
	t_cmd	*list;
	
	list = g_minishell.list_input;
	remove_quote_dollar(list);
	concat_tokens_same_type();
	detect_cmd_type();
	//debug();
	ft_switch(list);
	while (list != NULL)
	{
		if (list->content->type == semicolon || list->content->type == pipeline) 
		{
			while (list->next && list->content->type != cmd_instr)
				list = list->next;
			//printf("value: %s\n", list->content->value);
			ft_switch(list);
		}
		list = list->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:47:41 by user42            #+#    #+#             */
/*   Updated: 2021/12/07 16:04:50 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	*get_path_pwd(char **env)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_strdup((env[i] + 4));
			break ;
		}
	}
	return (path);
}

/* 
** tmp = /bin/echo
** args[0] = echo
** args[1->fin] : aux arguments (bonjour je suis Corentin)
*/

static char	*find_slash(void *s)
{
	size_t	i;
	char	*char_s;
	char	*ret;

	char_s = (char *)s;
	i = ft_strlen(char_s);
	i--;
	while (char_s[i] && char_s[i] != '/')
		i--;
	ret = ft_strdup(&char_s[++i]);
	return (ret);
}

static char	**add_arguments(t_cmd *list)
{
	char	**ret;
	size_t	nb_args;
	size_t	i;
	t_cmd	*begin;

	begin = list;
	i = 1;
	nb_args = 0;
	while (ft_isstop(list) != 0)
	{	
		if (list->content->type == literal)
			nb_args++;
		list = list->next;
	}
	list = begin;
	ret = malloc(sizeof(char *) * (nb_args + 2));
	ret[0] = find_slash(list->content->value);
	ret[nb_args + 1] = NULL;
	while (i < nb_args + 1)
	{
		list = list->next;
		if (list->content->type == literal)
			ret[i++] = list->content->value;
	}
	return (ret);
}

static void	execute_child(t_cmd *list)
{
	char	*path;
	char	**args;
	char	*tmp;

	if (check_exec(list->content->value) == True)
	{
		tmp = ft_split(list->content->value, ' ')[0];
		args = add_arguments(list);
	}
	else
	{
		args = ft_split(list->content->value, '/');
		path = get_path_pwd(g_minishell.env);
		tmp = ft_strjoin(path, "/");
		free(path);
		tmp = ft_strjoin_free(tmp, args[1]);
	}
	execve(tmp, args, g_minishell.env);
	free(tmp);
	free_array(args);
	if (errno)
		g_minishell.last_return_value = errno;
	else
		g_minishell.last_return_value = 0;
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
	if (!pid)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != STDOUT_FILENO)
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

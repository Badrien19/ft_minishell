/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:15:10 by user42            #+#    #+#             */
/*   Updated: 2021/12/10 17:01:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_exit_2(int in, int out, int exit_value)
{
	int		pid;

	if ((in == 0 && out == 1 ) || exit_value == -1)
	{
		ft_putstr_fd("exit\n", 1);
		if (exit_value == -1)
		{
			printf("minishell: exit: bad argument\n");
			exit_value = 0;
		}
		free_list();
		exit(exit_value);
	}
	pid = fork();
	if(pid == -1)
		cmd_error();
	if (!pid)
		exit(exit_value);
	else
	{
		waitpid(pid, NULL, 0);
		if (out != STDOUT_FILENO)
			close(out);
		if (in != STDIN_FILENO)
			close(in);
	}
}

void	cmd_exit(t_cmd *list)
{
	int		exit_value;
	int		i;
	int		in;
	int		out;

	exit_value = 0;
	in = list->content->pipe_in;
	out = list->content->pipe_out;
	i = -1;
	list = list->next;
	while (list && list->content->type == space && list->next)
		list = list->next;
	while (list && ((char *)list->content->value)[++i])
		if (ft_isalpha(((char *)list->content->value)[i]))
			exit_value = -1;
	if (list && exit_value != -1)
		exit_value = ft_atoi((char *)list->content->value);
	cmd_exit_2(in, out, exit_value);
}

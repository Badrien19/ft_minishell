/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:10:19 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:10:19 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	tokenizer(char *input)
{
	t_cmd			*new;
	char			*value;
	t_token			*token;
	t_token_type	type;

	value = ft_strdup(input);
	if (!value)
		exit(-1);
	type = find_type(value[0]);
	token = create_token(value, type);
	new = ft_cmdnew(token);
	if (!new)
		exit (-1);
	ft_cmdadd_back(&g_minishell.list_input, new);
}

void	detect_cmd_type(void)
{
	t_bool	already_cmd;

	already_cmd = False;
	while (g_minishell.list_input)
	{
		if (already_cmd == False
				&& (!ft_strcmp(g_minishell.list_input->content->value, "echo")
				|| !ft_strcmp(g_minishell.list_input->content->value, "cd")
				|| !ft_strcmp(g_minishell.list_input->content->value, "pwd")
				|| !ft_strcmp(g_minishell.list_input->content->value, "export")
				|| !ft_strcmp(g_minishell.list_input->content->value, "unset")
				|| !ft_strcmp(g_minishell.list_input->content->value, "env")
				|| !ft_strcmp(g_minishell.list_input->content->value, "exit")
				|| !ft_strncmp(g_minishell.list_input->content->value, "./", 2)
				|| check_path(g_minishell.list_input->content->value) == True))
		{
			g_minishell.list_input->content->type = cmd_instr;
			already_cmd = True;
		}
		if (get_token_type(g_minishell.list_input->content) == pipeline
			|| get_token_type(g_minishell.list_input->content) == semicolon)
			already_cmd = False;
		if (g_minishell.list_input->next)
			g_minishell.list_input = g_minishell.list_input->next;
		else
			break;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

void	pre_parsing(char *user_input)
{
	char	*new;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(user_input);
	while (i < size)
	{
		new = ft_strndup(user_input + i, 1);
		tokenizer(new);
		free(new);
		i++;
	}
	concat_tokens_same_type();
	concat_tokens_var();
	detect_cmd_type();
	if (checking_if_quotes_even() == True)
		concat_tokens_quotes();
	else
		g_minishell.parsing_error = True;
}

void	parsing(char *user_input)
{
	pre_parsing(user_input);
	while (g_minishell.list_input->next)
	{
		if (get_token_type(g_minishell.list_input->content)
			== simple_redir_right)
			parse_simple_redirection_right();
		else if (get_token_type(g_minishell.list_input->content)
			== double_redir_right)
			parse_double_redirection_right();
		else if (get_token_type(g_minishell.list_input->content)
			== simple_redir_left)
			parse_simple_redirection_left();
		else if (get_token_type(g_minishell.list_input->content)
			== double_redir_left)
			parse_double_redirection_left();
		else if (get_token_type(g_minishell.list_input->content)
			== pipeline)
			parse_pipe();
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

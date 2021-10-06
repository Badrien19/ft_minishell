#include "../../includes/ft_minishell.h"

void    tokenizer(char *input)
{
	t_cmd			*new;
	char            *value;
	t_token         *token;
	t_token_type	type;

	value = ft_strdup(input);
	if (!value)
		exit(-1);
	type = find_type(value[0]);
	token = create_token(value, type);
	if (!(new = ft_cmdnew(token)))
		exit (-1);
	ft_cmdadd_back(&g_minishell.list_input, new);
}

void	detect_cmd_type(void)
{
	t_cmd *begin;

	begin = g_minishell.list_input;
	while (g_minishell.list_input)
	{
		if (!ft_strcmp(g_minishell.list_input->content->value, "echo") || 
		!ft_strcmp(g_minishell.list_input->content->value, "cd") ||
		!ft_strcmp(g_minishell.list_input->content->value, "pwd") ||
		!ft_strcmp(g_minishell.list_input->content->value, "export") ||
		!ft_strcmp(g_minishell.list_input->content->value, "unset") ||
		!ft_strcmp(g_minishell.list_input->content->value, "env") ||
		!ft_strcmp(g_minishell.list_input->content->value, "exit") ||
		!ft_strcmp(g_minishell.list_input->content->value, "./"))
			g_minishell.list_input->content->type = cmd_instr;
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = begin;
}

void	check_pipes(void)
{
	t_cmd	*tmp;
	t_cmd	*prev_cmd;
	t_cmd	*next_cmd;
	int		fd[2];

	while (g_minishell.list_input->next)
	{
		if (g_minishell.list_input->content->type == pipeline)
		{	
			tmp = g_minishell.list_input;
			if (pipe(fd) == -1)
				return ; // Erreur
			prev_cmd = find_prev_cmd();
			prev_cmd->content->pipe_out = fd[0];
			g_minishell.list_input = tmp;
			next_cmd = find_next_cmd();
			next_cmd->content->pipe_in = fd[1];
		}
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

t_bool	parsing(char *user_input)
{
	char *new;
	size_t i;
	size_t size;

	i = 0;
	size = ft_strlen(user_input);
	if (size == 0)
		return (False);
	while (i < size)
	{
		new = ft_strndup(user_input + i, 1);
		tokenizer(new);
		free(new);
		i++;
	}
	concat_tokens_same_type();
	detect_cmd_type();
	//print_current_chain(); DEBUG
   // printf("__TEST1__\n");
	concat_tokens_var();
	//printf("__TEST2__\n");
	if (concat_tokens_quotes() == False)
		return (False);
	check_redirection_and_pipe();
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
	return (True);
}

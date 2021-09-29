#include "../../includes/ft_minishell.h"

static	t_token			g_tab_token[] = {
	{"|", pipeline},
	{"<", simple_redir_left},
	{">", simple_redir_right},
	{"<<", double_redir_left},
	{">>", double_redir_right},
	{";", semicolon},
	{"\"", double_quote},
	{"'", single_quote},
	{"\\", backslash},
	{"\f", space},
	{"\n", line_return},
	{"\r", space},
	{"\t", space},
	{"\v", space},
	{" ", space},
	{"$", variable},
	{0, 0},
};

t_token *create_token(char *value, t_token_type type)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!(token))
		exit(-1);
	token->value = value;
	token->type = type;
	token->pipe_in = STDIN_FILENO;
	token->pipe_out = STDOUT_FILENO;
	//printf("New Token ! ('%s' - %i)\n", (char *)token->value, token->type);
	return (token);
}

t_token_type find_type(char c)
{
	size_t i;
	char *str;
	t_token_type type;

	i = 0;
	type = none;
	while (g_tab_token[i].value)
	{
		str = g_tab_token[i].value;
		if (str[0] == c)
		{
			type = g_tab_token[i].type;
			return (type);
		}
		i++;
	}
	if (type == none)
		if (ft_isalpha(c))
			type = literal;
	return (type);
}

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

t_cmd	*find_next_cmd(void)
{
	while (g_minishell.list_input)
	{
		if (g_minishell.list_input->content->type == cmd_instr)
			return (g_minishell.list_input);
		g_minishell.list_input = g_minishell.list_input->next;
	}
	return (g_minishell.list_input);
}

t_cmd	*find_prev_cmd(void)
{
	while (g_minishell.list_input)
	{
		if (g_minishell.list_input->content->type == cmd_instr)
			return (g_minishell.list_input);
		g_minishell.list_input = g_minishell.list_input->prev;
	}
	return (g_minishell.list_input);
}

void	check_redirection(void)
{
	t_cmd	*begin;
	int		fd;

	begin = g_minishell.list_input;
	while (g_minishell.list_input)
	{
		if (g_minishell.list_input->content->type == simple_redir_left || g_minishell.list_input->content->type == double_redir_left)
		{
			fd = open(g_minishell.list_input->next->next->content->value, O_RDONLY);
			if (!fd)
				return ; // Erreur
			g_minishell.list_input = find_next_cmd();
			g_minishell.list_input->content->pipe_in = fd;
		}
		if (g_minishell.list_input->content->type == simple_redir_right || g_minishell.list_input->content->type == double_redir_right)
		{
			fd = open(g_minishell.list_input->next->next->content->value, O_WRONLY);
			if (!fd)
				return ; // Erreur
			g_minishell.list_input = find_next_cmd();
			g_minishell.list_input->content->pipe_out = fd;
		}
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = begin;
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
		!ft_strcmp(g_minishell.list_input->content->value, "exit"))
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

	while (g_minishell.list_input)
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
	g_minishell.list_input = tmp;
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
	check_redirection();
	check_pipes();
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
	return (True);
}

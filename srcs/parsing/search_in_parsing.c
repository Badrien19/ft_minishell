#include "../../includes/ft_minishell.h"

t_cmd	*find_next_cmd(void)
{
	t_cmd *current;
	t_cmd *ret;

	current = g_minishell.list_input;
    g_minishell.list_input = g_minishell.list_input->next; // Vérifier si ça ne pose pas problème.
	while (g_minishell.list_input && g_minishell.list_input->content->type != cmd_instr
	&& g_minishell.list_input->content->type != pipeline)
		g_minishell.list_input = g_minishell.list_input->next;
	if (g_minishell.list_input && g_minishell.list_input->content->type == pipeline)
		ret = NULL;
	else
		ret = g_minishell.list_input;
	g_minishell.list_input = current;
	return (ret);
}

t_cmd	*find_prev_cmd(void)
{
	t_cmd *current;
	t_cmd *ret;

	current = g_minishell.list_input;
    g_minishell.list_input = g_minishell.list_input->prev; // Vérifier si ça ne pose pas problème.
	while (g_minishell.list_input && g_minishell.list_input->content->type != cmd_instr
	&& g_minishell.list_input->content->type != pipeline)
		g_minishell.list_input = g_minishell.list_input->prev;
	if (g_minishell.list_input && g_minishell.list_input->content->type == pipeline)
		ret = NULL;
	else
		ret = g_minishell.list_input;
	g_minishell.list_input = current;
	return (ret);
}

t_cmd	*find_next_literal(void)
{
	t_cmd *current;
	t_cmd *ret;

	current = g_minishell.list_input;
	while (g_minishell.list_input && g_minishell.list_input->content->type != literal
	&& g_minishell.list_input->content->type != pipeline)
		g_minishell.list_input = g_minishell.list_input->next;
	if (g_minishell.list_input && g_minishell.list_input->content->type == pipeline)
		ret = NULL;
	else
		ret = g_minishell.list_input;
	g_minishell.list_input = current;
	return (ret);
}
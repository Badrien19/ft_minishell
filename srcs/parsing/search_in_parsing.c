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

/* find_next_literal(size_t range)
** range : Jusqu'à combien de node (en ignorant les espaces) chercher le literal. 0 = pas de limite.
** S'arrête automatiquement dès qu'il trouve un '|' ou la fin de la chaine.
*/
t_cmd	*find_next_literal(int range)
{
	t_cmd *current;
	t_cmd *ret;

	if (range == 0)
		range = ft_cmdsize(g_minishell.list_input);
	else
		range++;
	current = g_minishell.list_input;
	while (g_minishell.list_input && g_minishell.list_input->content->type != literal
	&& g_minishell.list_input->content->type != pipeline && range > 0)
	{
		if (g_minishell.list_input->content->type != space)
			range--;
		g_minishell.list_input = g_minishell.list_input->next;
	}
	if ((g_minishell.list_input && g_minishell.list_input->content->type == pipeline) || range <= 0)
		ret = NULL;
	else
		ret = g_minishell.list_input;
	g_minishell.list_input = current;
	return (ret);
}
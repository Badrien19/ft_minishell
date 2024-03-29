#include "../../includes/ft_minishell.h"

static char *replace_by_name(t_token_type nb)
{
	if (nb == 0)
		return ("space");
	else if (nb == 1)
		return ("line_return");
	else if (nb == 2)
		return ("pipeline");
	else if (nb == 3)
		return ("semicolon");
	else if (nb == 4)
		return ("simple_redir_left");
	else if (nb == 5)
		return ("simple_redir_right");
	else if (nb == 6)
		return ("double_redir_left");
	else if (nb == 7)
		return ("double_redir_right");
	else if (nb == 8)
		return ("single_quote");
	else if (nb == 9)
		return ("double_quote");
	else if (nb == 10)
		return ("backslash");
	else if (nb == 11)
		return ("variable");
	else if (nb == 12)
		return ("litteral");
	else if (nb == 13)
		return ("cmd_instr");
	else if (nb == 14)
		return ("filename");
	else if (nb == 15)
		return ("none");
	return(NULL);
}

static void	print_list(void)
{
	t_cmd	*begin;

	begin = g_minishell.list_input;
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
	if (g_minishell.list_input != NULL)
	{
		while (g_minishell.list_input != NULL)
		{
			printf("%-20s | %-18s | %5d | %5d | %14p | %14p\n", (char*)g_minishell.list_input->content->value, replace_by_name(g_minishell.list_input->content->type), g_minishell.list_input->content->pipe_in, g_minishell.list_input->content->pipe_out, g_minishell.list_input->prev, g_minishell.list_input->next);
			g_minishell.list_input = g_minishell.list_input->next;
		}
	}
	g_minishell.list_input = begin;
}

void	print_current_chain(void)
{
	t_cmd *begin = g_minishell.list_input;

	while (g_minishell.list_input)
	{
		printf("'%s'", (char *)g_minishell.list_input->content->value);
		if (g_minishell.list_input->next)
			printf(" -> ");
		g_minishell.list_input = g_minishell.list_input->next;
	}
	printf("\n");
	g_minishell.list_input = begin;
}

void	debug(void)
{
	printf("-------------------------------------------DEBUG-------------------------------------------\n");
	printf("%-20s   %-18s   %5s   %5s  %14s  %14s\n", "Name", "Type", "In", "Out", "Prev Address", "Next Address");
	print_list();
	printf("-------------------------------------------------------------------------------------------\n\n");
}

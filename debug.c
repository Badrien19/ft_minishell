#include "includes/ft_minishell.h"

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
	else if (nb == 9)
		return ("single_quote");
	else if (nb == 10)
		return ("double_quote");
	else if (nb == 11)
		return ("backslash");
	else if (nb == 12)
		return ("variable");
	else if (nb == 13)
		return ("litteral");
}

static void	print_list(void)
{
	t_list	*begin;

	begin = g_minishell.list_input;
	if (g_minishell.list_input != NULL)
	{
		while (g_minishell.list_input != NULL)
		{
			printf("%-15s | %-12s | %16p\n", (char*)g_minishell.list_input->content->value, replace_by_name(g_minishell.list_input->content->type), g_minishell.list_input->next);
			g_minishell.list_input = g_minishell.list_input->next;
		}
	}
	g_minishell.list_input = begin;
}

void	print_current_chain(void)
{
	t_list *begin = g_minishell.list_input;

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
	printf("----------------------DEBUG----------------------\n");
	print_list();
	printf("-------------------------------------------------\n\n");
}
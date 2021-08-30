#include "includes/ft_minishell.h"

static void	print_list(void)
{
	t_node	*list;

	list = g_minishell.list_input;
	if (list != NULL)
	{
		while (list->next != NULL)
		{
			printf("%-20s (%2i) -> %18p\n", (char*)list->content->value, list->content->type, list->next);
			list = list->next;
		}
		//printf("'%-10s' (%2i) -> %25p\n", (char*)list->content->value, list->content->type, list->next);
	}
}

void	debug(void)
{
	printf("---------------------DEBUG---------------------\n");
	print_list();
	printf("-----------------------------------------------\n\n");
}
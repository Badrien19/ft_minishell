#include "ft_minishell.h"

t_bool	checking_if_quotes_even(void)
{
	t_list	*list;
	int		count_s;
	int		count_d;

	list = g_sys_infos.list_input;
	count_s = 0;
	count_d = 0;

	if (list == NULL)
		error("List is empty.\n");
	while (list)
	{
		if(list->content->type == single_quote)
			count_s++;
		else if(list->content->type == double_quote)
			count_d++;
		list = list->next;
	}
	if (count_s % 2 != 0 || count_d % 2 != 0)
	{
		printf("Warning : Quotes are uneven.\n");
		return (False);
	}
	else
		return (True);
}

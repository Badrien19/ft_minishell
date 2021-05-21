#include "ft_minishell.h"

t_bool	checking_if_quotes_even(void)
{
	t_list	*list;
	int		quote;

	list = g_sys_infos.list_input;
	quote = 0;
	if (list == NULL)
		error("List is empty.\n");
	while (list && list->next)
	{	
		if(list->content->type == 9)
			quote = 1;
			while (quote == 1)
			{
				if(list->next)
					list = list->next;				
				else
					return ;
				if(list->content->type == 1 || list->content->type == 3)
				{
					printf("Warning : Quotes are uneven.\n");
					free_list();
					main();
				}
				if(list->content->type == 9)
					quote = 0;
			}
			if(list->content->type == 10)
				quote = 1;
			while (quote == 1)
			{
				if(list->next)
					list = list->next;				
				else
					return ;
				if(list->content->type == 1 || list->content->type == 3)
				{
					printf("Warning : Quotes are uneven.\n");
					free_list();
					main();
				}
				if(list->content->type == 10)
					quote = 0;
			}
				list = list->next;
	}
	return (True);
}

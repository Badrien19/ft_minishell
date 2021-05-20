#include "ft_minishell.h"

void    print_list(void)
{
	t_sys_infos tmp_sys_infos;
	
	tmp_sys_infos = g_sys_infos;
	printf("\n---------------------DEBUG---------------------\n");
	if (tmp_sys_infos.list_input != NULL)
	{
		while (tmp_sys_infos.list_input->next != NULL)
		{
			printf("%-20s (%2i) -> %18p\n", (char*)tmp_sys_infos.list_input->content->value, tmp_sys_infos.list_input->content->type, tmp_sys_infos.list_input->next);
			tmp_sys_infos.list_input = tmp_sys_infos.list_input->next;
		}
		//printf("'%-10s' (%2i) -> %25p\n", (char*)tmp_sys_infos.list_input->content->value, tmp_sys_infos.list_input->content->type, tmp_sys_infos.list_input->next);
	}
	printf("-----------------------------------------------\n");
}
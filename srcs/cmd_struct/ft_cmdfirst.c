#include "../../includes/ft_minishell.h"

t_cmd	*ft_cmdfirst(t_cmd *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}
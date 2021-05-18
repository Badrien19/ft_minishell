/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:24:05 by badrien           #+#    #+#             */
/*   Updated: 2021/05/18 16:07:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"


void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (new != NULL)
	{
		if (*alst != NULL)
			ft_lstlast(*alst)->next = new;
		else
			*alst = new;
	}
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst != NULL && del != NULL)
	{
		if ((*lst)->next != NULL)
			ft_lstclear(&(*lst)->next, del);
		ft_lstdelone(*lst, del);
		*lst = NULL;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst != 0 && del != 0)
		del(lst->content);
	free(lst);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst != NULL && f != NULL)
	{
		while (lst->next != NULL)
		{
			f(lst->content);
			lst = lst->next;
		}
		f(lst->content);
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	unsigned int	i;

	if (lst != NULL)
	{
		i = 0;
		while (lst != NULL)
		{
			lst = lst->next;
			i++;
		}
		return (i);
	}
	return (0);
}

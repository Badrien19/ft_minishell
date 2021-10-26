/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:42:29 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/06/11 01:05:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_cmd	*ft_cmdnew(void *content)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!(new))
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:38:44 by cgoncalv          #+#    #+#             */
/*   Updated: 2019/10/16 18:13:36 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

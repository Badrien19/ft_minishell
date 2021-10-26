/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:41:20 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/05/27 19:21:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_cmdadd_back(t_cmd **alst, t_cmd *new)
{
	if (new == NULL)
		return ;
	if (*alst != NULL)
	{
		new->prev = ft_cmdlast(*alst);
		ft_cmdlast(*alst)->next = new;
	}
	else
		*alst = new;
}

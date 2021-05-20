/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:28:08 by user42            #+#    #+#             */
/*   Updated: 2021/05/20 16:44:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void error(char *error_text)
{
    ft_putstr(error_text, 1);
    // Appel à fonction qui free tout
    exit (0);
}
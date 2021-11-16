/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:28:08 by user42            #+#    #+#             */
/*   Updated: 2021/11/16 17:06:39 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	error(char *error_text)
{
	ft_putstr_fd(error_text, 2);
	free_list();
	exit (0);
}

void	parsing_error(int error_code)
{
	if (error_code == MS_ERROR_PARSE)
		write(2, "minishell: parse error\n", 24);
	else if (error_code == MS_ERROR_TOO_MANY_ARG)
		write(2, "minishell: too many arguments\n", 30);
	else if (error_code == MS_ERROR_TO_PERROR)
		perror("minishell");
	else if (error_code == MS_ERROR_NO_CMD)
		write(2, "minishell: command not found.\n", 30);
	else if (error_code == MS_ERROR_INVALID_QUOTE)
		write(2, "minishell: quote are uneven.\n", 29);
	g_minishell.parsing_error = True;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walker <walker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 09:57:55 by user42            #+#    #+#             */
/*   Updated: 2021/08/27 17:38:08 by walker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	sigstp_handler(int sig)
{
	printf("SIGSTP_PRESSED\n");
}

int	main(int argc, char **argv, char **env)
{
	char	*user_input;
	
	
	signal(SIGTSTP, &sigstp_handler);
	g_minishell.list_input = 0;
	g_minishell.env = env;
	while (True)
	{
		g_minishell.parsing_error = False;
		user_input = readline("\033[1;32mminishell >\033[0m ");
		if (user_input && *user_input)
		{
			add_history(user_input);
			parsing(user_input);
		}
		if (g_minishell.parsing_error == False)
		{
			debug();
			cmd_hub();
		}
		free_list();
	}
	return (EXIT_SUCCESS);
}

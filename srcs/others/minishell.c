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

void	SIGINT_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "\0\n", 2);
		write(STDOUT_FILENO, "\n\033[1;32mminishell >\033[0m ", 24);
		signal(SIGINT, &SIGINT_handler);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*user_input;
	
	signal(SIGINT, &SIGINT_handler);
	user_input = NULL;
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
		if (user_input && ft_strlen(user_input) != 0 && g_minishell.parsing_error == False)
		{
			debug();
			cmd_hub();
		}
		else if (!user_input)
			exit(EXIT_SUCCESS);
		free_list();
	}
	return (EXIT_SUCCESS);
}
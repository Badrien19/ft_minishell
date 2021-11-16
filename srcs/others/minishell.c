/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:37:03 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/11/16 16:37:46 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "\0\n", 2);
		write(STDOUT_FILENO, "\n\033[1;32mminishell >\033[0m ", 24);
		signal(SIGINT, &sigint_handler);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*user_input;

	signal(SIGINT, &sigint_handler);
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
		if (user_input && ft_strlen(user_input) != 0
			&& g_minishell.parsing_error == False)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:37:03 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/11/17 14:55:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	sigint_handler(int sig)
{
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	char	*user_input;

	signal(SIGINT, &sigint_handler);
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

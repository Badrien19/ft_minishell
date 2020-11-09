/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:58:05 by badrien           #+#    #+#             */
/*   Updated: 2020/11/03 14:58:05 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void     cmd_parser(char *cmd, t_env *lst)
{
    char **tab;
    size_t i;

    i = 0;
    tab = ft_split(cmd, ';');
    while (tab[i])
    {
        // echo "oui" | cat -e > text.txt
		
		if (ft_strstr(tab[i], "echo") != NULL)
            cmd_echo(&tab[i][5]);
        else if (ft_strstr(tab[i], "exit") != NULL)
            cmd_exit(tab[i]);
        else if (ft_strstr(tab[i], "pwd") != NULL)
            cmd_pwd();
        else if (ft_strstr(tab[i], "env") != NULL)
            print_lst(lst);
        else
        {   
            write(1, "minishell: command not found: ", 30);
            write(1, tab[i], ft_strlen(tab[i]));
        }
        i++;
    }
}

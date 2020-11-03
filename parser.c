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

void     cmd_parser(char *cmd)
{
    char **tab;
    size_t i;

    i = 0;
    tab = ft_split(cmd, ';');
    while (tab[i])
    {
        if (ft_strstr(tab[i], "echo") != NULL)
            cmd_echo(&tab[i][5]);
        else if (ft_strstr(tab[i], "exit") != NULL)
            cmd_exit(tab[i]);
        else if (ft_strstr(tab[i], "pwd") != NULL)
            cmd_pwd();
        else
        {   
            write(1, "minishell: command not found: ", 30);
            write(1, tab[i], ft_strlen(tab[i]));
        }
        i++;
    }
}

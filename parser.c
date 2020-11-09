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

/*
**  Les guillemets '' (Affiche \) et "" (N'affiche pas \)
**  Le backslash (Annule la prochaine commande)
**  Le dollars $ (Permet de lancer une commande)
*/

// echo "$oui" | cat -e > text.txt

// 1. Guillemets (Sauf si \)
// 2. Dollars (Sauf si \) (Attention à \\)
// 3. CMD

char    *next_arg(char *s)
{
    char *tmp;
    char *ret;
    char c;
    size_t i;
    size_t backslash;
    i = 0;
    backslash = 0;

    tmp = ft_strtrim(s, " ");
    while (tmp[i])
    {
        while (tmp[i] = '\\')
        {
            backslash++;
            i++;
        }
        if (backslash != 0)
        {
            ret = ft_straddnchar('\\', (backslash / 2));
            if (backslash % 2 != 0)
            {
                ret = ft_straddnchar(tmp[i + 1], 1);
                i++;
            }
        }
        if (tmp[i] == '"' || tmp[i] == "'")
        {
            c = tmp[i];
            while (tmp[i] != c && tmp[i])
                i++;
        }
        i++;
    }
    return (tmp);
}

void     cmd_parser(char *cmd, t_env *lst)
{
    char **tab;
    size_t i;
    size_t j;
    t_cmd *l_cmd;

    i = 0;
    tab = ft_split(cmd, ';');
    
    while(tab[i])
    {
        j = 0;
        l_cmd = malloc(sizeof(t_cmd));

        l_cmd->args[j] = next_arg(tab[i]); 
        i++;
    }

    /*
    while (tab[i])
    {
        // echo "$oui" | cat -e > text.txt
		
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
    */
}

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
        if (ft_strstr(tab[i], "exit") != NULL)
            cmd_exit(tab[i]);
        if (ft_strstr(tab[i], "pwd") != NULL)
            cmd_pwd();
        i++;
    }
}

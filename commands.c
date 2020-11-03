#include "ft_minishell.h"

void     cmd_echo(char *cmd)
{
    int     flag_n;
    char    type_quote;
    size_t  i;

    i = 0;
    flag_n = 0;
    type_quote = 0;
    while (cmd[i] == ' ')
        i++;
    if (ft_strncmp(cmd, "-n ", 3) == 0)
    {
        flag_n = 1;
        i += 3;
    }
    while (cmd[i])
    {
        if ((cmd[i] == '"' || cmd[i] == '\''))
        {    
            if(type_quote == 0)
                type_quote = cmd[i];
            else if(type_quote == cmd[i])
                type_quote = 0;
            else // donc " et ' ou l'inverse
                write(1, &cmd[i], 1);
        }
        else
            write(1, &cmd[i], 1);
        i++;
    }
    if (flag_n == 1) // TODO
        write(1, "\0", 1);
    if (cmd[i - 1] != '\n' && i > 0)
        write(1, "\n", 1);
}

void     cmd_pwd()
{
    char *buff;

    buff = malloc(sizeof(char) * 512);
    getcwd(buff, 512);
    write(1, buff, ft_strlen(buff));
    write(1, "\n", 1);
}

void     cmd_exit(char *cmd)
{
    exit(1);
}
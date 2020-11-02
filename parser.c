#include "ft_minishell.h"

int     cmd_parser(char *cmd)
{
    if (ft_strstr(cmd, "echo") != NULL)
        cmd_echo(&cmd[5]);
    if (ft_strstr(cmd, "exit") != NULL)
        cmd_exit(cmd);
}

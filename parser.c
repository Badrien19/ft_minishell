#include "ft_minishell.h"

void     cmd_parser(char *cmd)
{
    if (ft_strstr(cmd, "echo") != NULL)
        cmd_echo(&cmd[5]);
    if (ft_strstr(cmd, "exit") != NULL)
        cmd_exit(cmd);
    if (ft_strstr(cmd, "pwd") != NULL)
        cmd_pwd();
    if (ft_strstr(cmd, "cd") != NULL)
        cmd_cd(&cmd[3]);
}

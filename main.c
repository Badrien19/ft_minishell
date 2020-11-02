#include "ft_minishell.h"

char	*stradd(char *s1, char const *s2)
{
	char	*ret;
	size_t	size_s1;
	size_t	size_s2;

    size_s1 = 0;
    if (s1 != NULL)
	    size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!(ret = malloc((sizeof(char) * (size_s1 + size_s2) + 1))))
		return (NULL);
	if (s1 != NULL)
	{
		ft_memcpy(ret, s1, size_s1);
		ft_memcpy(&ret[size_s1], s2, size_s2 + 1);
		free(s1);
	}
	else
		ft_memcpy(ret, s2, size_s2 + 1);
	return (ret);
}

char    *read_cmd()
{
    char    buff[BUFFER + 1];
    char    *str;
    size_t  ret;

    str = NULL;
    while (1)
    {
        ret = read(1, buff, BUFFER);
        buff[ret] = 0;
        str = stradd(str, buff);
        if (ft_strchr(buff, '\n') != NULL)
            break;
    }
    return (str);
}

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
        if ((cmd[i] == '"' || cmd[i] == '\'') && type_quote == 0)
            type_quote = cmd[i];
        if (cmd[i] != type_quote)
            write(1, &cmd[i], 1);
        i++;
    }
    if (flag_n == 1) // TODO
        write(1, "\0", 1);
}

void     cmd_exit(char *cmd)
{
    exit(1);
}

int     cmd_parser(char *cmd)
{
    if (ft_strstr(cmd, "echo") != NULL)
        cmd_echo(&cmd[5]);
    if (ft_strstr(cmd, "exit") != NULL)
        cmd_exit(cmd);
}

void    preface()
{
    write(1, "\033[1;32m", 7);
    write(1, "minishell >", 12);
    write(1, "\033[0m", 4);
}

int     main(int argc, char *argv[])
{
    char *cmd;

    cmd = NULL;
    while (1)
    {
        preface();
        cmd = read_cmd();
        cmd_parser(cmd);
    }
    
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:44:13 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/11/09 16:44:13 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

#define SH_TOK_BUFFSIZE 64

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

char    *sh_read_line()
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

void    sh_pre()
{
    write(1, "\033[1;32m", 7);
    write(1, "minishell > ", 13);
    write(1, "\033[0m", 4);
}

void	sh_loop()
{
	char	*line;
	char	**cmd;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		sh_pre();
		line = sh_read_line();
		cmd = ft_split(line, ';');
		while (cmd)
		{
			// Gérer les variables env ($)
			args = 	ft_split(cmd, ' '); // Version modifiée de split. (sh_split_line) (Quote)
			// Remplir la structure
			*cmd++;
		}
		//status = sh_execute((cmd));
		free(line);
		free(cmd);
	}
}

int		main(int argc, char **argv)
{

    sh_loop();

    return EXIT_SUCCESS;
}
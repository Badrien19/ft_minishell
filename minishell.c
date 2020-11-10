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

#define SH_LINE_BUFFSIZE 10
#define SH_LINE_DELIM " \t\r\n\a"

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
    char    buff[SH_LINE_BUFFSIZE + 1];
    char    *str;
    size_t  ret;

    str = NULL;
    while (1)
    {
        ret = read(1, buff, SH_LINE_BUFFSIZE);
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
	size_t	k = 0;

	// __TEST__ //
	size_t i = 0;

	status = 1;
	while (status)
	{
		k = 0;
		sh_pre();
		line = sh_read_line();
		cmd = ft_split(line, ';');

		// __TEST__ //
		i = 0;
		while (cmd[i])
		{
			printf("cmd[%li] : ´%.*s´\n", i, ft_strlen(cmd[i]) - 1, cmd[i]); // Attention aux retour à la ligne
			i++;
		}
		printf("----------\n");

		while (cmd[k])
		{
			// Gérer les variables env ($)
			args = 	sh_split_line(cmd[k], SH_LINE_DELIM);

			// __TEST__ //
			i = 0;
			while (args[i])
			{
				printf("arg[%li] ´%.*s´\n", i, ft_strlen(args[i]) - 1, args[i]);
				i++;
			}

			// Remplir la structure
			k++;
		}
		//status = sh_execute((cmd));
		free(line);
		//free(cmd);
	}
}

int		main(int argc, char **argv)
{

    sh_loop();

    return EXIT_SUCCESS;
}
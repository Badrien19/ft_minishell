/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/11/04 15:42:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static int	ft_int_strrchr(char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (c == s[i])
			return (i);
		i--;
	}
	if (c == s[i])
		return (i);
	return (0);
}

static void	pwd_remove(void)
{
	int		end;
	char	*tmp;

	tmp = g_minishell.env[envchr("PWD") + 1];
	end = ft_int_strrchr(tmp, '/');
	g_minishell.env[envchr("PWD") + 1] = ft_strdup(tmp - end);
	printf("pwd = %s\n", g_minishell.env[envchr("PWD") + 1]);
	
}

static void	pwd_add(char *value)
{
	char	*tmp;

	tmp = g_minishell.env[envchr("PWD")];
	if (tmp[ft_strlen(tmp) - 1] != '/')
		tmp =  ft_strjoin(tmp, "/");
	g_minishell.env[envchr("PWD")] = ft_strjoin(tmp, value);
	printf("pwd = %s\n", g_minishell.env[envchr("PWD")]);
}

void	cmd_cd(t_cmd *list)
{
	int		ret;
	int		pid;
	char	*cwd;

	errno = 0;
	pid = fork();
	ret = chdir(list->content->value);
	printf("\nentry -> %s\n", (char *)list->content->value);
	if(!pid)
	{
		if (ret == -1)
			printf("%s : %s\n", (char*)list->content->value, strerror(errno));
		else
		{
			printf("Successfuly changed directory.\n"); // Temporaire
			if(!ft_strcmp((char *)list->content->value, ".."))
				pwd_remove();
			else
				pwd_add((char *)list->content->value);
			if (errno == ERANGE)
				printf("<error> : %s\n", strerror(errno));
			//else
				//free(cwd);
		}
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
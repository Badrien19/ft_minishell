/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:53:10 by user42            #+#    #+#             */
/*   Updated: 2021/11/16 13:51:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	*ft_strcut(char *str, size_t size)
{
	char	*array;

	array = ft_strdup(str);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, array, size + 1);
	str[size] = '\0';
	free(array);
	array = NULL;
	return (str);
}

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

	tmp = g_minishell.env[envchr("PWD")];
	end = ft_int_strrchr(tmp, '/');
	tmp = ft_strcut(tmp, end);
	g_minishell.env[envchr("PWD")] = ft_strdup(tmp);
}

static void	pwd_add(char *value)
{
	char	*tmp;

	tmp = g_minishell.env[envchr("PWD")];
	tmp = ft_strjoin(tmp, "/");
	if (value[ft_strlen(value) - 1] == '/')
		value = ft_strcut(value, (ft_strlen(value) - 1));
	g_minishell.env[envchr("PWD")] = ft_strjoin(tmp, value);
}

void	cmd_cd(t_cmd *list)
{
	int		ret;
	char	*cwd;

	errno = 0;
	ret = chdir(list->content->value);
	if (ret == -1)
		printf("%s : %s\n", (char *)list->content->value, strerror(errno));
	else
	{
		if (!ft_strcmp((char *)list->content->value, ".."))
			pwd_remove();
		else
			pwd_add((char *)list->content->value);
		if (errno == ERANGE)
			printf("<error> : %s\n", strerror(errno));
	}
}

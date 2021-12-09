/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:17:37 by badrien           #+#    #+#             */
/*   Updated: 2021/12/09 11:39:20 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

char	*get_value_env(char *name)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = 0;
	tmp = NULL;
	while (name[len] != '\0' && name[len] != ' ' && name[len] != '$'
		&& name[len] != '\"' && name[len] != '\'' && name[len] != '/'
		&& name[len] != '=')
		len++;
	if (len == 0)
		return (NULL);
	while (g_minishell.env[++i] != NULL)
	{
		if (ft_strncmp(g_minishell.env[i], name, len) == 0)
		{
			tmp = ft_substr(g_minishell.env[i],
					(len + 1), ft_strlen(g_minishell.env[i]));
			if (tmp == NULL)
				cmd_error();
			return (tmp);
		}
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*rep;

	if (s == NULL)
		return (NULL);
	i = 0;
	rep = malloc((sizeof(char) * (len + 1)));
	if (!rep)
		cmd_error();
	if (!(start > ft_strlen(s)))
	{
		while (i < len && s[start + i] != '\0')
		{
			rep[i] = s[start + i];
			i++;
		}
	}
	rep[i] = '\0';
	return (rep);
}

void	print_env(void)
{
	int	x;

	x = 0;
	while (g_minishell.env[x] != NULL)
	{
		printf("%s\n", g_minishell.env[x]);
		x++;
	}
}

char	**realloc_env(char **env, size_t size)
{
	char	**new;
	size_t	i;

	i = 0;
	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = NULL;
	while (env[i] != NULL && i < size)
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			cmd_error();
		i++;
	}
	if (g_minishell.env)
		free_array(g_minishell.env);
	return (new);
}

int	size_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:17:37 by badrien           #+#    #+#             */
/*   Updated: 2021/11/25 16:02:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*rep;

	if (s == NULL)
		return (NULL);
	i = 0;
	rep = malloc((sizeof(char) * (len + 1)));
	if (!rep)
		errro("Malloc error\n");
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

void	print_env(void) // Vérifier les strings dans le tableau env
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
			error("Malloc error\n");
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

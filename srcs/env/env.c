/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:17:37 by badrien           #+#    #+#             */
/*   Updated: 2021/09/30 15:08:31 by badrien          ###   ########.fr       */
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
	if ((rep = malloc((sizeof(char) * (len + 1)))) == 0)
		return (0);
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

void print_env() // Vérifier les strings dans le tableau env
{
	int x;
	x = 0;

	printf("TEST4\n");
	while(g_minishell.env[x] != NULL)
	{
		printf("%s\n", g_minishell.env[x]);
		x++;
	}
}

char **realloc_env(int size)
{
	char    **new;
	int i;
	
	i = 0;
	new = malloc(sizeof(char *) * (size + 1));
	if (new==NULL)
		return NULL;
	new[size] = NULL;
	while(g_minishell.env[i] != NULL && i < size)
	{
		new[i] = ft_strdup(g_minishell.env[i]);
		i++;
	}
	while(g_minishell.env[i] != NULL)
	    free(g_minishell.env[i++]);
	return (new);
}

int size_env()
{
	int i;

	i = 0;
	while(g_minishell.env[i] != NULL)
		i++;
	return (i);
}

int add_env(char *name, char *value)
{
	printf("Enter add env\n");
	char *tmp;
	
	if (name == NULL || value == NULL)
		return (1);
	printf("lauch realloc\n");
	g_minishell.env = realloc_env(size_env() + 1);
	if (g_minishell.env == NULL)
		return (1);
	tmp = ft_strjoin("=", value);
	g_minishell.env[size_env() - 1] = ft_strjoin(name, tmp);
	free(tmp);
	return(0);
}

int main_env()
{
	add_env("test","test");
	printf("OK\n");
	//print_env(g_minishell.env);
	printf("value of USER = %s\n", get_value_env("PWD"));
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:17:37 by badrien           #+#    #+#             */
/*   Updated: 2021/06/01 09:24:30 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minishell.h"

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

void print_env()
{
    int x;
    x = 0;

    while(g_sys_infos.env[x] != NULL)
    {
        printf("%s\n", g_sys_infos.env[x]);
        x++;
    }
}

char **realloc_env(int size)
{
    printf("Enter realloc env\n");
	char    **new;
    int i;
    
    i = 0;
    new = malloc(sizeof(char *) * (size + 1));
    if (new==NULL)
        return NULL;
    printf("begin copy\n");
	new[size] = NULL;
	while(g_sys_infos.env[i] != NULL && i < size)
    {
		new[i] = ft_strdup(g_sys_infos.env[i]);
		i++;
	}
	//printf("begin free\n");
	//i = 0;
    //while(g_sys_infos.env[i] != NULL)
    //    free(g_sys_infos.env[i++]);
    printf("end\n");
	/*
    int x;
    x = 0;
	printf("printing new\n");
    while(new[x] != NULL)
    {
        printf("%s\n", new[x]);
        x++;
    }
	printf("end printing new\n");
	*/
	return (new);
}

int size_env()
{
    int i;

	i = 0;
    while(g_sys_infos.env[i] != NULL)
		i++;
    return (i);
}

char *get_value_env(char *name)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(name);
    while(g_sys_infos.env[i] != NULL)
    {
        if(ft_strncmp(g_sys_infos.env[i], name, len) == 0)
        {
			return(ft_substr(g_sys_infos.env[i], (len + 1), ft_strlen(g_sys_infos.env[i])));
		}
		i++;
    }
    return (NULL);
}

int add_env(char *name, char *value)
{
    printf("Enter add env\n");
	char *tmp;
    
    if(name == NULL || value == NULL)
        return (1);
	printf("lauch realloc\n");
    g_sys_infos.env = realloc_env(size_env() + 1);
    if(g_sys_infos.env == NULL)
        return (1);
    tmp = ft_strjoin("=", value);
    g_sys_infos.env[size_env() - 1] = ft_strjoin(name, tmp);
	free(tmp);
    return(0);
}

int main_env()
{
	add_env("test","test");
	printf("OK\n");
	//print_env(g_sys_infos.env);
	printf("value of USER = %s\n", get_value_env("PWD"));
	return (0);
}
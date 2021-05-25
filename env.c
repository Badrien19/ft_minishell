/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:17:37 by badrien           #+#    #+#             */
/*   Updated: 2021/05/25 14:42:22 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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
/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen((char *)s1);
	if (!(ret = malloc(sizeof(char) * (i + ft_strlen((char*)s2) + 1))))
		return (0);
	ft_memcpy(ret, s1, i);
	ft_memcpy(&ret[i], s2, ft_strlen((char*)s2) + 1);
	return (ret);
}
*/

/*
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
*/

/*
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int i;

	i = 0;
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (dest);
}
*/
/*
size_t	ft_strlen(const char *chaine)
{
	size_t i;

	i = 0;
	while (chaine[i] != '\0')
		i++;
	return (i);
}
*/
/*
char	*ft_strdup(const char *s)
{
	char			*new;

	if ((new = malloc(sizeof(char) * ft_strlen((char *)s) + 1)) == 0)
		return (NULL);
	ft_memcpy(new, (char*)s, ft_strlen((char *)s) + 1);
	return (new);
}
*/

void print_env(char **env)
{
    int x;
    x = 0;

    while(env[x] != NULL)
    {
        printf("%s\n", env[x]);
        x++;
    }
}

char **realloc_env(char **env, int size)
{
    char    **new;
    int i;
    
    i = 0;
    new = malloc(sizeof(char *) * (size + 1));
    if (new==NULL)
        return NULL;
    while(env[i] != NULL && i < size)
        new[i] = ft_strdup(env[i++]);
    new[size] = NULL;
    while(env++ != NULL)
        free(env);
    return (new);
}

int size_env(char **env)
{
    int i;

    while(env[i] != NULL)
        i++;
    return (i);
}

char *get_value_env(char **env, char *name)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(name);
    while(env[i] != NULL)
    {
        if(ft_strncmp(env[i], name, len) != 1)
            return(ft_substr(env[i], (len + 1), ft_strlen(env[i])));
        i++;
    }
    return (NULL);
}

int add_env(char **env, char *name, char *value)
{
    char *tmp;
    
    if(name == NULL || value == NULL)
        return (1);
    env = realloc_env(env, size_env(env) + 1);
    if(env == NULL)
        return (1);
    tmp = ft_strjoin("=", value);
    env[size_env(env) - 1] = ft_strjoin(name, tmp);
    return(0);
}

int main_env(char **env)
{
	print_env(env);
	
	return (0);
}
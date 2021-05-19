/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:17:37 by badrien           #+#    #+#             */
/*   Updated: 2021/05/19 11:27:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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
    env[size_env(env) - 1] = strjoin(name, tmp);
    return(0);
}

//ajouter par Alex

int     init_env(char **env_array)
{
    t_list  *env;
    t_list  *new;
    int     i;

    env = malloc(sizeof(t_list));
    if (env == NULL)
        return (0);
    env->value = ft_strdup(env_array[0]);
    env->next = NULL;
    i = 1;
    while (env_array && env_array[0] && env_array[i])
    {
        new = malloc(sizeof(t_list));
        if (new == NULL)
            return (0);
        new->value = ft_strdup(env_array[i]);
        new->next = NULL;
        env->next = new;
        i++;
    }
    return(0);
}

void    ft_env(t_list *env)
{
    while (env && env->next)
    {
        ft_putendl(env->value);
        env = env->next;
    }
    if(env)
        ft_putendl(env->value);
}
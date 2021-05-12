/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:23:16 by badrien           #+#    #+#             */
/*   Updated: 2020/11/09 10:23:16 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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

char    *read_cmd()
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

void    preface()
{
    write(1, "\033[1;32m", 7);
    write(1, "minishell >", 12);
    write(1, "\033[0m", 4);
}

t_env *lst_add_env(char *name, char *content)
{
	t_env *new;
	
	if (!(new = malloc(sizeof(t_env))))
		return (0);
	new->name = name;
	new->content = content;
	new->next = NULL;

	return (new);
}

void print_lst(t_env *lst)
{
	if(lst == NULL)
		return;
	while(lst != NULL)
	{
		printf("Name:'%s' content:'%s'\n", lst->name, lst->content);
		lst = lst->next;
	}
}

t_env *create_env(char **env)
{
	t_env *start;
	t_env *lst;
	
	char *name;
	char *content;
	int i;
	int j;

	i = 0;
	j = 0;
	while(env[i])
    {
		while(env[i][j] != '=')
			j++;
		name = ft_substr(env[i], 0, j);
		content = ft_substr(env[i], j+1, ft_strlen(env[i]) - (j + 1));
		
		if(i == 0)
		{
			lst = lst_add_env(name, content);
			start = lst;
		}	
		else
		{
			lst->next = lst_add_env(name, content);
			lst = lst->next;
		}
		j = 0;
		i++;
    }
	//print_lst(start);
	return(start);
}

int     main(int argc, char *argv[], char** env)
{
    char *cmd;
    cmd = NULL;
    
    t_env *l_env;
    l_env = create_env(env);
	//printf("TEST\n");
	//printf("%p\n",l_env);
	//printf("Name:'%s' content:'%s'\n", l_env->name, l_env->content);
	//print_lst(l_env);

    while (1)
    {
        preface();
        cmd = read_cmd();
        cmd_parser(cmd, l_env);
    }
    
    return (0);
}
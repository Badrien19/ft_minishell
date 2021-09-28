/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:17:37 by badrien           #+#    #+#             */
/*   Updated: 2021/09/28 15:25:59 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minishell.h"

char *get_value_env(char *name)
{
	int i;
	int len;

	i = 0;
	len = 0;
	printf("name = (%s)\n\n", name);
	while(name[len] != '\0' && name[len] != ' ' && name[len] != '$' && name[len] != '\"' && name[len] != '\'')
		len++;
	//printf("len %d\n", len);
	while(g_minishell.env[i] != NULL)
	{
		if(ft_strncmp(g_minishell.env[i], name, len) == 0)
		{
			return(ft_substr(g_minishell.env[i], (len + 1), ft_strlen(g_minishell.env[i])));
		}
		i++;
	}
	return (NULL);
}

int apply_dollar(t_list *list) // UTILISER UN SPLIT $
{
	int i;
	char *value;

	while(list != NULL)
	{
		value = list->content->value;
		i = 0;
		/*if(list->content->type == double_quote)
		{
			while (value[i] != '\0')
			{
				if(value[i] == '$')
					list->content->value = get_dollar_value(value);
				i++;
			}
		}*/
		if(list->content->type == variable)
		{
			list->content->value = get_value_env(value + 1);
			list->content->type = literal;
		}
	list = list->next;
	}

	return (0);
	//if(list->content->type=variable)
}


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

	while(g_minishell.env[x] != NULL)
	{
		printf("%s\n", g_minishell.env[x]);
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
	while(g_minishell.env[i] != NULL && i < size)
	{
		new[i] = ft_strdup(g_minishell.env[i]);
		i++;
	}
	//printf("begin free\n");
	//i = 0;
	//while(g_minishell.env[i] != NULL)
	//    free(g_minishell.env[i++]);
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
	while(g_minishell.env[i] != NULL)
		i++;
	return (i);
}

char *apply_quote(char *data)
{
	int quote;
	int double_quote;
	char *buff;
	char *tmp;
	int nb;
	int i;
	int x;

	quote = 0;
	double_quote = 0;
	nb = 0;
	i = 0;
	x= 0;

	while(data[x] != '\0')
	{
		printf("Data[%d] = %c \n",x , data[x]);
		if(data[x] == '\"' && quote%2 == 0) // Si on tombe sur un " et qu'on est pas dans un ' '
			double_quote++;
		else if(data[x] == '\'' && double_quote%2 == 0) // Si on tombe sur un ' et qu'on est pas dans un " "
			quote++;
		else if(data[x] == '$' && quote%2 != 1) // On skip que si on est Dans un ' '
		{
			while(data[x + i] != '\0' || data[x + i] != ' ')
				i++;
			ft_strjoin(buff, get_value_env(ft_substr(data, 1, (i - 1))));
			i = 0;
		}
		else
		{
			
		}
		x++;
	}
	if(double_quote%2 == 1 || quote%2 == 1)
		return (NULL);
	return(buff);
}

int add_env(t_list *list)
{
	printf("Enter add env\n");
	char	*tmp;
	int i;
	tmp = apply_quote(list->content->value);	
	
	printf("TEST: (%s)\nDONE: (%s)",list->content->value ,tmp);



	printf("lauch realloc\n");
	g_minishell.env = realloc_env(size_env() + 1);
	if (g_minishell.env == NULL)
		return (1);
	g_minishell.env[size_env() - 1] = tmp;
	free(tmp);

	print_env();

	return(0);
}

int main_env()
{
	//add_env("test","test");
	printf("OK\n");
	//print_env(g_minishell.env);
	printf("value of USER = %s\n", get_value_env("PWD"));
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:19:59 by badrien           #+#    #+#             */
/*   Updated: 2021/09/30 15:23:56 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int new_str_len(char *str)
{
	int i;
	int quote;
	int double_quote;
	
	i = 0;
	quote = 0;
	double_quote = 0;
	
	while(str[i] != '\0')
	{
		if(str[i] == '\'' && double_quote%2 == 0)
			quote++;
		else if(str[i] == '\"' && quote%2 == 0)
			double_quote++;
		i++;
	}
	if(quote%2 == 1 || double_quote%2 == 1)
		return(-1);
	return(i - quote - double_quote);
}

char *remove_quote(char *str, int len)
{
	char *new_str;
	int quote;
	int double_quote;
	int i;

	i = 0;
	quote = 0;
	double_quote = 0;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return(NULL);
	len = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '\'' && double_quote%2 == 0)
		{
			i++;
			quote++;
		}
		else if(str[i] == '\"' && quote%2 == 0)
		{
			i++;
			double_quote++;
		}
		else
		{
			new_str[len] = str[i];
			len++;
			i++;
		}
	}
	new_str[len] = '\0';
	return (new_str);
}

char *apply_quotes(char *str) // OK
{
	int i;
	int len;
	char *new_str;

	i = 0;
	len = new_str_len(str);
	if(len == -1)
	{
		printf("quote not even\n");
		exit(-1);
	}
	printf("strlen = %lu\n", strlen(str));
	printf("New len = %d\n", len);
	new_str= remove_quote(str, len);
	printf("new_str = %s\n", new_str);

	return(new_str);
}

char *get_value_env(char *name)
{
	int i;
	int len;
	//char c;

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
	//c = '$';
	//return ((char *)c);
	return (NULL);
}

int size_str(char *str)
{
	int i;
	int len;

	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '$')
			len += ft_strlen(get_value_env(&str[i]));
		i++;
	}
	return(i + len);
}

char *apply_dollar(char *str)
{
	int len;
	int i;
	char *new;
	char *tmp;

	len = size_str(str);
	printf("size_str = %d", len);
	i = 0;

	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	len = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '$')
		{
			tmp = get_value_env(&str[i]);
			new = ft_strjoin(new, tmp);
			len = ft_strlen(new);
			while(str[i] != '\0' && str[i]  != ' ' && str[i]  != '$')
				i++;
		}
		new[len] = str[i];
	}
	new[len] = '\0';
	return(new); 
}

int remove_quote_dollar(t_cmd *list)
{
	int i;
	char *value;

	while(list != NULL)
	{
		value = list->content->value;
		i = 0;
		if(list->content->type == double_quote || list->content->type == single_quote) // OK
		{
			list->content->value = apply_quotes(list->content->value);
			//list->content->type = literal;
		}
		//if(list->content->type == double_quote) // TO DO
		//	list->content->value = apply_dollar(value);
		if(list->content->type == variable) // OK
		{
			list->content->value = get_value_env(value + 1);
			list->content->type = literal;
		}
		//free(value);
		list = list->next;
	}

	return (0);
	//if(list->content->type=variable)
}

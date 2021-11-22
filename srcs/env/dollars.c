/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:19:59 by badrien           #+#    #+#             */
/*   Updated: 2021/11/21 14:09:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	get_quote_len(char *str)
{
	int	i;
	int	quote;
	int	double_quote;

	i = 0;
	quote = 0;
	double_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
			quote++;
		else if (str[i] == '\"' && quote % 2 == 0)
			double_quote++;
		i++;
	}
	if (quote % 2 == 1 || double_quote % 2 == 1)
		return (-1);
	return (i - quote - double_quote);
}

static char	*remove_quote_2(char *str, int len)
{
	char	*new_str;
	int		quote;
	int		double_quote;
	int		i;

	i = 0;
	quote = 0;
	double_quote = 0;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
		{
			i++;
			quote++;
		}
		else if (str[i] == '\"' && quote % 2 == 0)
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

static char	*remove_quote(char *str)
{
	int		len;

	len = get_quote_len(str);
	if (len == -1)
	{
		printf("quote not even\n");
		exit(-1);
	}
	return (remove_quote_2(str, len));
}

char	*get_value_env(char *name)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (name[len] != '\0' && name[len] != ' '
		&& name[len] != '$' && name[len] != '\"' && name[len] != '\'')
		len++;
	while (g_minishell.env[i] != NULL)
	{
		if (ft_strncmp(g_minishell.env[i], name, len) == 0)
		{
			return (ft_substr(g_minishell.env[i],
					(len + 1), ft_strlen(g_minishell.env[i])));
		}
		i++;
	}
	return (NULL);
}

static int	get_dollar_len(char *str)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				len += ft_strlen(ft_itoa(g_minishell.last_return_value));
			}
			else
			{
				i++;
				tmp = get_value_env(&str[i]);
				if (tmp != NULL)
					len += ft_strlen(tmp);
				free(tmp);
				//len += ft_strlen(get_value_env(&str[i]));
				while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
					i++;
			}
		}
		i++;
		len++;
	}
	return (len - 1);
}

static char	*dollar_to_value(char *str)
{
	int		len;
	int		i;
	char	*new;
	char	*tmp;

	len = get_dollar_len(str);
	new = NULL;
	i = 0;
	new = malloc(sizeof(char) * (len + 1));
	ft_bzero(new, len + 1);
	if (new == NULL)
		return (NULL);
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				new = ft_strjoin(new, ft_itoa(g_minishell.last_return_value));
				len += ft_strlen(ft_itoa(g_minishell.last_return_value));
				i += 2;
			}
			else
			{
				tmp = get_value_env(&str[i + 1]);
				if (tmp != NULL)
					new = ft_strjoin(new, tmp);
				if (new != NULL)
					len = ft_strlen(new);
				i++;
			}
			while (str[i] != '\0' && str[i]  != ' ' && str[i]  != '$'
				&& str[i]  != '\'' && str[i]  != '\"')
				i++;
		}
		new[len] = str[i];
		i++;
		len++;
	}
	new[len] = '\0';
	return (new); 
}

int	replace_value_from_env(t_cmd *list)
{
	//char	*value;

	while (list != NULL)
	{
		//value = list->content->value;
		if(ft_isstop(list) == 0)
			return(0);
		if (list->content->type == double_quote || list->content->type == single_quote) // OK
		{
			list->content->value = remove_quote(list->content->value);
			list->content->type = literal;
		}
		if (list->content->type == double_quote) // OK $?
		{
			list->content->value = dollar_to_value(list->content->value);
		}
		if (list->content->type == variable) // OK
		{
			list->content->value = dollar_to_value(list->content->value);
			//printf("value = (%s)\n",(char *)list->content->value);
			list->content->type = literal;
			//if(list->content->value == NULL)
			//	list->content->type = none;
			//debug();
		}
		if (((char *)list->content->value)[0] == '\0')
			list->content->type = none;
		//free(value);
		list = list->next;
	}
	//debug();
	//g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
	return (0);
	//if(list->content->type=variable)
}

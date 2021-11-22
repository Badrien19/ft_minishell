/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:19:59 by badrien           #+#    #+#             */
/*   Updated: 2021/11/22 19:12:27 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

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
				len += ft_strlen(ft_itoa(g_minishell.last_return_value));
			else
			{
				tmp = get_value_env(&str[++i]);
				if (tmp != NULL)
					len += ft_strlen(tmp);
				free(tmp);
				while (str[i + 1] != '\0' && str[i] != ' ' && str[i] != '$')
					i++;
			}
		}
		len++;
		i++;
	}
	return (len - 1);
}

static char	*next_dollar_value(int *i, int *len, char *str)
{
	char	*new;

	new = NULL;
	if (str[*i + 1] == '?')
	{
		new = ft_strjoin_free(new,
				ft_itoa(g_minishell.last_return_value));
		len += ft_strlen(ft_itoa(g_minishell.last_return_value));
		*i += 2;
	}
	else
	{
		new = get_value_env(&str[*i + 1]);
		if (new != NULL)
			*len += ft_strlen(new);
		(*i)++;
	}
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '$'
		&& str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	return (new);
}

static char	*dollar_to_value(char *str, int len)
{
	int		i;
	char	*new;
	char	*tmp;

	len = get_dollar_len(str);
	new = NULL;
	i = 0;
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, len + 1);
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			tmp = next_dollar_value(&i, &len, str);
			if	(tmp != NULL)
				new = ft_strjoin_free(new, tmp);
			free(tmp);
		}
		else
			new[len++] = str[i++];
	}
	new[len] = '\0';
	free(str);
	return (new);
}

int	replace_value_from_env(t_cmd *list)
{
	while (list != NULL)
	{
		if (ft_isstop(list) == 0)
			return (0);
		if (list->content->type == double_quote
			|| list->content->type == single_quote)
		{
			list->content->value = remove_quote(list->content->value);
		}
		if (list->content->type == double_quote)
		{
			list->content->value = dollar_to_value(list->content->value, 0);
		}
		if (list->content->type == variable)
		{
			list->content->value = dollar_to_value(list->content->value, 0);
			list->content->type = literal;
		}
		if (((char *)list->content->value)[0] == '\0')
			list->content->type = none;
		list = list->next;
	}
	return (0);
}

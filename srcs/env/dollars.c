/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:19:59 by badrien           #+#    #+#             */
/*   Updated: 2021/11/25 16:00:32 by user42           ###   ########.fr       */
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
		&& name[len] != '$' && name[len] != '\"' && name[len] != '\'' && name[len] != '/')
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
/*
static int	next_len_value(char *str)
{
	i++;
	if (str[i] == '?')
	{
		tmp = ft_itoa(g_minishell.last_return_value);
		len += ft_strlen(tmp);
		free(tmp);
	}
	else
	{
		tmp = get_value_env(&str[i]);
		if (tmp != NULL)
			len += ft_strlen(tmp);
		free(tmp);
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '$' && str[i] != '/')
			i++;
	}
}
*/
static int	get_dollar_len(char *str)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				tmp = ft_itoa(g_minishell.last_return_value);
				if (!tmp)
					error("Malloc error\n");
				len += ft_strlen(tmp);
				i++;
				free(tmp);
			}
			else
			{
				tmp = get_value_env(&str[i]);
				if (!tmp)
					error("Malloc error\n");
				if (tmp != NULL)
					len += ft_strlen(tmp);
				free(tmp);
				while (str[i] != '\0' && str[i] != ' ' && str[i] != '$' && str[i] != '/')
					i++;
			}
		}
		if (str[i] != '\0')
		{
			i++;
			len++;
		}
	}
	return (len);
}

static char	*next_dollar_value(int i, char *str)
{
	char	*new;
	char	*tmp;

	new = NULL;
	i++;
	if (str[i] == '?')
	{
		tmp = ft_itoa(g_minishell.last_return_value);
		if (!tmp)
			error("Malloc error\n");
		new = ft_strjoin_free(new, tmp);
		if (!new)
		{
			free(tmp);
			error("Malloc error\n");
		}
		free(tmp);
	}
	else
		new = get_value_env(&str[i]);
	return (new);
}

static char	*dollar_to_value(char *original_str, int len)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*env_value;

	i = 0;
	len = get_dollar_len(original_str);
	//printf("len = %d\n", len);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_str[len] = '\0';
	if (len != 0)
	{
		len = 0;
		while (original_str[i] != '\0')
		{
			if (original_str[i] != '$')
				new_str[len++] = original_str[i++];
			else
			{
				j = 0;
				env_value = next_dollar_value(i, original_str);
				while (env_value[j] != '\0')
					new_str[len++] = env_value[j++];
				i++;
				if (original_str[i] == '?')
					i++;
				else
					while (original_str[i] != '\0' && original_str[i] != ' ' && original_str[i] != '$' && original_str[i] != '/')
						i++;
				free(env_value);
			}
		}
	}
	free(original_str);
	return (new_str);
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
			list->content->type = literal;
		}
		if (list->content->type == double_quote)
		{
			list->content->value = dollar_to_value(list->content->value, 0);
			list->content->type = literal;
		}
		if (list->content->type == variable)
		{
			list->content->value = dollar_to_value(list->content->value, 0);
			list->content->type = literal;
		}
		if (((char *)list->content->value)[0] == '\0')
			list->content->type = none;
		list = list->next;
		//debug();
	}
	return (0);
}

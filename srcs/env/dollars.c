/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:19:59 by badrien           #+#    #+#             */
/*   Updated: 2021/12/07 18:45:46 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

char	*get_value_env(char *name)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = 0;
	tmp = NULL;
	while (name[len] != '\0' && name[len] != ' ' && name[len] != '$'
		&& name[len] != '\"' && name[len] != '\'' && name[len] != '/'
		&& name[len] != '=')
		len++;
	if (len == 0)
		return (NULL);
	while (g_minishell.env[++i] != NULL)
	{
		if (ft_strncmp(g_minishell.env[i], name, len) == 0)
		{
			tmp = ft_substr(g_minishell.env[i],
					(len + 1), ft_strlen(g_minishell.env[i]));
			if (tmp == NULL)
				cmd_error();
			return (tmp);
		}
	}
	return (NULL);
}

static int	len_last_return_value(void)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = NULL;
	tmp = ft_itoa(g_minishell.last_return_value);
	if (!tmp)
		cmd_error();
	len = ft_strlen(tmp);
	free (tmp);
	return (len);
}

static int	len_block_var(char *str, size_t *i)
{
	int		len;
	char	*tmp;

	len = 0;
	if ((str[*i] == '\0' || ft_isalnum(str[*i]) == 0) && str[*i + 1] != '?')
		len++;
	else
	{
		tmp = get_value_env(&str[*i]);
		if (tmp != NULL)
			len += ft_strlen(tmp);
		free (tmp);
		while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '$'
			&& str[*i] != '/' && str[*i] != '=' && str[*i] != '\"'
			&& str[*i] != '\'')
			*i = *i + 1;
	}
	return (len);
}

static int	get_dollar_len(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				len += len_last_return_value();
				i++;
			}
			else
				len += len_block_var(str, &i);
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
			cmd_error();
		new = ft_strjoin_free(new, tmp);
		if (!new)
		{
			free(tmp);
			cmd_error();
		}
		free(tmp);
	}
	else
		new = get_value_env(&str[i]);
	return (new);
}

static int	len_without_space(char *original_str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (original_str[i + len] != '\0')
	{
		if (original_str[i + len] == ' ')
		{
			len++;
			while (original_str[i + len] == ' ')
				i++;
		}
		len++;
	}
	return (len);
}

char	*trim_space(char *str, char *original_str, t_cmd *list)
{
	char	*new;

	free (original_str);
	if (list->prev->content->type != literal)
	{
		new = ft_strtrim(str, " ");
		free (str);
		if (new == NULL)
			cmd_error();
		return (new);
	}
	else
		return (str);
}

static char	*remove_space(char *original_str, int len, t_cmd *list)
{
	char	*new;
	int		i;

	new = malloc (sizeof(char *) * (len_without_space(original_str) + 1));
	if (new == NULL)
	{
		free(original_str);
		cmd_error();
	}
	i = 0;
	len = 0;
	while (original_str[i] != '\0')
	{
		if (original_str[i] == ' ')
		{
			new[len++] = original_str[i++];
			while (original_str[i] == ' ')
				i++;
		}
		new[len++] = original_str[i++];
	}
	new[len] = '\0';
	return (trim_space(new, original_str, list));
}

static char	*dollar_to_value(char *original_str, int len)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*env_value;

	i = 0;
	len = get_dollar_len(original_str);
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
				if ((original_str[i + 1] == '\0'
						|| ft_isalnum(original_str[i + 1]) == 0)
					&& original_str[i + 1] != '?')
					new_str[len++] = original_str[i++];
				else
				{
					j = 0;
					env_value = next_dollar_value(i, original_str);
					while (env_value != NULL && env_value[j] != '\0')
						new_str[len++] = env_value[j++];
					i++;
					if (original_str[i] == '?')
						i++;
					else
						while (original_str[i] != '\0' && original_str[i] != ' ' && original_str[i] != '$' && original_str[i] != '/' && original_str[i] != '=' && original_str[i] != '\"' && original_str[i] != '\'')
							i++;
					free(env_value);
				}
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
		if (list->content->type == pipeline || list->content->type == semicolon)
			return (0);
		if (list->content->type == double_quote
			|| list->content->type == single_quote)
			list->content->value = remove_quote(list->content->value);
		if (list->content->type == double_quote)
			list->content->value = dollar_to_value(list->content->value, 0);
		if (list->content->type == variable)
		{
			list->content->value = dollar_to_value(list->content->value, 0);
			list->content->value = remove_space(list->content->value, 0, list);
		}
		if (list->content->type == double_quote || list->content->type
			== single_quote || list->content->type == variable)
			list->content->type = literal;
		if (((char *)list->content->value)[0] == '\0')
			list->content->type = none;
		if (list->prev && list->prev->content->type == literal
			&& list->content->type == none)
			list = delete_node(list);
		list = list->next;
	}
	return (0);
}

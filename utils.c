/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:58:10 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/11/09 22:58:10 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	detect_quote(char *str)
{
	size_t	i;
	char	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			quote = '"';
			break;
		}
		else if (str[i] == '\'')
		{
			quote = '\'';
			break;
		}
		i++;
	}
	return (quote);
}

char    *remove_quote(char *str)
{
	size_t  i;
	size_t  j;
	size_t	quote_n;
	char	quote;
	char	*tmp;

	i = 0;
	j = 0;
	quote_n = 0;
	quote = detect_quote(str);
	while (str[i])
		if (str[i++] == quote)
			quote_n++;
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(str) - quote_n))))
		return (NULL); // TODO : Créer une fonction de gestion d'erreur.
	i = 0;
	while (str[i])
	{
		if (str[i] != quote)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	tmp[j] = 0;
	return (tmp);
}

size_t  count_tok(char *str, char* charset)
{
	size_t  tok_n;
	size_t  i;
	size_t  j;
	size_t	quote_n;
	char	quote;
	BOOL	quote_open;

	tok_n = 0;
	i = 0;
	quote_n = 0;
	quote = 0;
	quote_open = FALSE;
	while (str[i])
	{
		j = 0;
		if (quote_open == FALSE)
			quote = detect_quote(&str[i]);
		if (str[i] == quote)
		{
			quote_n++;
			if (quote_n % 2 != 0)
				quote_open = TRUE;
			else
				quote_open = FALSE;
		}
		while (charset[j] && str[i] != charset[j])
			j++;
		if (str[i] == charset[j] && quote_open == FALSE)
			tok_n++;
		i++;
	}
	printf("tok_n : %li\n", tok_n);
	return (tok_n);
}

BOOL	try_charset(char c, char *charset)
{
	size_t i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*copy_str(char *src, size_t size)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!(dst = malloc(sizeof(char) * size + 1)))
		return (NULL); // TODO : Créer une fonction de gestion d'erreur.
	while (src[i] && i <= size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[size + 1] = '\0';
	return (dst);
}

char	**sh_split_line(char *str, char* charset)
{
	size_t	k;
	size_t  i;
	size_t  j;
	size_t	start;
	char	quote;
	char	**tab;

	k = 0;
	i = 0;
	j = 0;
	quote = 0;
	if (!(tab = malloc(sizeof(char *) * count_tok(str, charset) + 1)))
		return (NULL); // TODO : Créer une fonction de gestion d'erreur.
	while (str[i] && k < count_tok(str, charset))
	{
		while (str[i] && try_charset(str[i], charset))
			i++;
		// 1. S'il y a une parenthèse, copier jusqu'à la prochaine 
		quote = detect_quote(&str[i]);
		printf("quote : %c\n", quote);
		if (str[i] == quote)
		{
			start = i++;
			while (str[i] && str[i] != quote)
				i++;
			printf("1. start : %li - i : %li\n", start, i);
			tab[k] = copy_str(&str[start], i - start);
			tab[k] = remove_quote(tab[k]);
			k++;
			continue;
		}
		// 2. Passer tous les charsets
		while (str[i] && try_charset(str[i], charset))
			i++;
		start = i;
		// 3. Dès que ce n'est plus un charset, compter le nombre de char jusqu'au prochain charset. Retenir le début
		while (str[i] && !try_charset(str[i], charset))
			i++;
		// 4. Copier entre début et fin
		printf("2. start : %li - i : %li\n", start, i);
		tab[k] = copy_str(&str[start], i - start);
		k++;
	}
	tab[k] = NULL;
	return (tab);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:51:50 by cgoncalv          #+#    #+#             */
/*   Updated: 2019/10/22 13:50:38 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**free_mllc(char **splitted, size_t k)
{
	size_t i;

	i = -1;
	while (++i > k)
		free(splitted[i]);
	free(splitted);
	return (0);
}

static size_t	nbr_str(char const *s, char c)
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue;
		}
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	start;
	char	**splitted;

	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	if (!(splitted = (char**)malloc(sizeof(char*) * (nbr_str(s, c) + 1))))
		return (NULL);
	while (s[i] && k < (nbr_str(s, c)))
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (!(splitted[k] = malloc(sizeof(char) * ((i - start) + 1))))
			return (free_mllc(splitted, k));
		ft_strlcpy(splitted[k], &s[start], i - start + 1);
		k++;
	}
	splitted[k] = NULL;
	return (splitted);
}

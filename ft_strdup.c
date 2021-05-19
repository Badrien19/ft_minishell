/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 10:47:58 by user42            #+#    #+#             */
/*   Updated: 2021/05/19 10:48:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_strdup(const char *s)
{
	char			*str;
	unsigned int	n;

	n = ft_strlen(s);
	if (!(str = malloc((sizeof(char) * (n + 1)))))
		return (NULL);
	ft_strlcpy(str, s, n + 1);
	str[n] = '\0';
	return (str);
}
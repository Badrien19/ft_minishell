/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:59:57 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 14:59:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minishell.h"

int		str_double_quote_check(void *s)
{
	char	*str;
	int		i;

	i = 1;
	str = (char *)s;
	printf("str : %s \n", str);
	while (str[i] && str[i] != double_quote)
	{
		printf("str[%i] : %c\n", i, str[i]);
		i++;
		if(str[i] == double_quote)
			return(True);
	}
	return(False);
}

int		str_single_quote_check(void *s)
{
	char	*str;
	int		i;

	i = 1;
	str =(char *) s;
	while (str[i] && str[i] != single_quote)
	{
		i++;
		if(str[i] == single_quote)	
			return(True);
	}
	return(False);

}

t_bool	checking_if_quotes_even(void)
{
	t_list	*list;

	list = g_sys_infos.list_input;
	while (list)
	{
		if (list->content->type == double_quote)
			if(str_double_quote_check(list->content->value))
			{
				printf("Quotes are uneven.\n");
				free_list();
				return(False);
			}
		printf("TEST 1\n");
		if (list->content->type == single_quote)
			if(str_single_quote_check(list->content->value))
			{
				free_list();
				return(False);
			}
		printf("TEST 2\n");
		if (list->next)
			list = list->next;
		else
			return(True);
		printf("TEST 3\n");
	}
	printf("TEST 4\n");
	return (True);
}

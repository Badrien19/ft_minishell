/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_concat_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:29:55 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:29:55 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	*join_two_tokens(t_token *token_1, t_token *token_2)
{
	char	*str_1;
	char	*str_2;
	char	*new_tok_value;
	t_token	*token;

	str_1 = token_1->value;
	str_2 = token_2->value;
	new_tok_value = ft_strjoin(str_1, str_2);
	token = create_token(new_tok_value, get_token_type(token_1));
	free(token_1->value);
	free(token_1);
	return (token);
}

static void	clear_node(t_cmd *node)
{
	node->content = NULL;
	free(node->content);
	node->next = NULL;
	free(node->next);
	free(node);
}

/* Fusionne le token actuel avec le token suivant 
** et garde le type du token actuel. 
*/
void	relink_nodes(void)
{
	t_cmd	*tmp_list;

	tmp_list = NULL;
	g_minishell.list_input->content = join_two_tokens(
			g_minishell.list_input->content,
			g_minishell.list_input->next->content);
	if (g_minishell.list_input->next->next)
		tmp_list = g_minishell.list_input->next->next;
	else
	{
		clear_node(g_minishell.list_input->next);
		g_minishell.list_input->next = NULL;
	}
	if (tmp_list)
	{
		g_minishell.list_input->next = tmp_list;
	}
}

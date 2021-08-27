#include "../includes/ft_minishell.h"

void *join_two_tokens(t_token *token_1, t_token *token_2)
{
    char *str_1;
    char *str_2;
    char *new_tok_value;
    t_token *token;

    str_1 = token_1->value;
    str_2 = token_2->value;
    //printf("%s - %s\n", str_1, str_2);
    new_tok_value = ft_strjoin(str_1, str_2);
    token = create_token(new_tok_value, get_token_type(token_1));
    //printf("%s\n", token->value);
    return (token);
}

static void clear_node(t_list *node)
{
    node->content = NULL;
	node->next = NULL;
}

void    relink_nodes()
{
    t_list *tmp_list;

    g_minishell.list_input->content = join_two_tokens(g_minishell.list_input->content, g_minishell.list_input->next->content);
    //printf("relink : %s\n", g_minishell.list_input->content->value);
    if (g_minishell.list_input->next->next)
        tmp_list = g_minishell.list_input->next->next;
    else
    {
        tmp_list->content = create_token(NULL, 0);
        tmp_list->next = NULL;
    }
    clear_node(g_minishell.list_input->next);
    g_minishell.list_input->next->content = tmp_list->content;
    g_minishell.list_input->next->next = tmp_list->next;
}
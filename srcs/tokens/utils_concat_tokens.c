#include "../../includes/ft_minishell.h"

void *join_two_tokens(t_token *token_1, t_token *token_2) // Free
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
    free(token_1->value);
    free(token_1);
    return (token);
}

static void clear_node(t_cmd *node)
{
    node->content = NULL;
    free(node->content);
	node->next = NULL;
    free(node->next);
    free(node);
}

/* Fusionne le token actuel avec le token suivant et garde le type du token actuel. */
void    relink_nodes()
{
    t_cmd *tmp_list;

    tmp_list = NULL;
    g_minishell.list_input->content = join_two_tokens(g_minishell.list_input->content, g_minishell.list_input->next->content);
    //printf("relink : %s\n", g_minishell.list_input->content->value);
    if (g_minishell.list_input->next->next)
        tmp_list = g_minishell.list_input->next->next;
    else
    {
    /*  tmp_list = malloc(sizeof(t_list));
        if (!(tmp_list))
            exit(-1);
        tmp_list->content = create_token(NULL, 0);
        tmp_list->next = NULL; */
        clear_node(g_minishell.list_input->next);
        g_minishell.list_input->next = NULL;
    }
    if (tmp_list)
    {
        g_minishell.list_input->next = tmp_list;
    }
    //print_current_chain();
}
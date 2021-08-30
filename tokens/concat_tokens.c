#include "../includes/ft_minishell.h"

void    concat_tokens_all()
{
    t_node *tmp_list;
    t_node *begin;

    begin = g_minishell.list_input;

    while (g_minishell.list_input != NULL && g_minishell.list_input->next != NULL)
    {
        //printf("'%s' -> '%s'\n", g_minishell.list_input->content->value, g_minishell.list_input->next->content->value);
        if (get_token_type(g_minishell.list_input->content) == single_quote
        || get_token_type(g_minishell.list_input->content) == double_quote)
            g_minishell.list_input = g_minishell.list_input->next;
        else if (get_token_type(g_minishell.list_input->content) == get_token_type(g_minishell.list_input->next->content)
        || (get_token_type(g_minishell.list_input->content) == variable && get_token_type(g_minishell.list_input->next->content) == literal))
            relink_nodes();
        else
            g_minishell.list_input = g_minishell.list_input->next;
    }
    g_minishell.list_input = begin;
}

t_bool    concat_no_spaces()
{
    t_node *begin;

    begin = g_minishell.list_input;
    while (g_minishell.list_input->next != NULL)
    {
        while (g_minishell.list_input->next->next != NULL 
        && g_minishell.list_input->next->content->type != space
        && g_minishell.list_input->content->type != space
        && g_minishell.list_input->content->type != single_quote
        && g_minishell.list_input->content->type != double_quote)
        {
            //printf("[in] %s\n", g_minishell.list_input->content->value);
            relink_nodes();
        }
        //printf("[out] %s\n", g_minishell.list_input->content->value);
        g_minishell.list_input = g_minishell.list_input->next;
    }
    g_minishell.list_input = begin;
}

static char get_last_char(void *value)
{
    size_t size;
    char *str;
    char ret;

    str = (char*)value;
    size = ft_strlen(str);
    ret = str[size - 1];

    return (ret);
}

t_bool  concat_tokens_quotes()
{
    t_node *begin;
    t_token_type quote_type;

    begin = g_minishell.list_input;
    if (checking_if_quotes_even() == False)
        return (False);
    while (g_minishell.list_input != NULL)
    {
        if (get_token_type(g_minishell.list_input->content) == single_quote || get_token_type(g_minishell.list_input->content) == double_quote)
        {
            quote_type = get_token_type(g_minishell.list_input->content);
            while ((get_token_type(g_minishell.list_input->next->content) != quote_type && g_minishell.list_input->next != NULL) || 
            (get_last_char(get_token_value(g_minishell.list_input->content)) == '\\' && get_token_type(g_minishell.list_input->next->content) == quote_type))
            {
                //printf("[in] s : %s -> %i\n", get_token_value(g_minishell.list_input->content), get_token_type(g_minishell.list_input->next->content));
                relink_nodes();
            }
            if (g_minishell.list_input->next && g_minishell.list_input->next->next)
            {
                //printf("[out] last : %c -> %i\n", get_last_char(get_token_value(g_minishell.list_input->content)), get_token_type(g_minishell.list_input->next->content));
                relink_nodes();
            }
        }
        g_minishell.list_input = g_minishell.list_input->next;
    }
    g_minishell.list_input = begin;
    return (True);
}

#include "../includes/ft_minishell.h"

void    concat_tokens_all()
{
    t_list *tmp_list;
    t_list *begin;

    begin = g_sys_infos.list_input;

    while (g_sys_infos.list_input != NULL && g_sys_infos.list_input->next != NULL)
    {
        //printf("'%s' -> '%s'\n", g_sys_infos.list_input->content->value, g_sys_infos.list_input->next->content->value);
        if (get_token_type(g_sys_infos.list_input->content) == get_token_type(g_sys_infos.list_input->next->content))
            relink_nodes();
        else
            g_sys_infos.list_input = g_sys_infos.list_input->next;
    }
    g_sys_infos.list_input = begin;
}

void    concat_no_spaces()
{
    t_list *begin;

    begin = g_sys_infos.list_input;
    while (g_sys_infos.list_input->next != NULL)
    {
        while (g_sys_infos.list_input->next->next != NULL && (g_sys_infos.list_input->next->content->type != space) && g_sys_infos.list_input->content->type != space)
        {
            //printf("[in] %s\n", g_sys_infos.list_input->content->value);
            relink_nodes();
        }
        //printf("[out] %s\n", g_sys_infos.list_input->content->value);
        g_sys_infos.list_input = g_sys_infos.list_input->next;
    }
    g_sys_infos.list_input = begin;
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
    t_list *begin;
    t_token_type quote_type;

    begin = g_sys_infos.list_input;
    if (checking_if_quotes_even() == False)
        return (False);
    while (g_sys_infos.list_input != NULL)
    {
        if (get_token_type(g_sys_infos.list_input->content) == single_quote || get_token_type(g_sys_infos.list_input->content) == double_quote)
        {
            quote_type = get_token_type(g_sys_infos.list_input->content);
            while ((get_token_type(g_sys_infos.list_input->next->content) != quote_type && g_sys_infos.list_input->next != NULL) || 
            (get_last_char(get_token_value(g_sys_infos.list_input->content)) == '\\' && get_token_type(g_sys_infos.list_input->next->content) == quote_type))
            {
                //printf("[in] last : %c -> %i\n", get_last_char(get_token_value(g_sys_infos.list_input->content)), get_token_type(g_sys_infos.list_input->next->content));
                relink_nodes();
            }
            //printf("[out] last : %c -> %i\n", get_last_char(get_token_value(g_sys_infos.list_input->content)), get_token_type(g_sys_infos.list_input->next->content));
            relink_nodes();
        }
        g_sys_infos.list_input = g_sys_infos.list_input->next;
    }
    g_sys_infos.list_input = begin;
    return (True);
}

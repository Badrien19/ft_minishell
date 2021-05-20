#include "ft_minishell.h"

static	t_token			g_tab_token[] = {
	{"|", pipeline},
	{"<", simple_redir_left},
	{">", simple_redir_right},
	{";", semicolon},
	{"\"", double_quote},
	{"'", single_quote},
	{"\\", backslash},
	{"\f", space},
	{"\n", space},
	{"\r", space},
	{"\t", space},
	{"\v", space},
	{" ", space},
	{"$", variable},
	{0, 0},
};

t_token *create_token(char *value, t_token_type type)
{
    t_token *token;
    
    token = malloc(sizeof(t_token));
    if (!(token))
        exit(-1);
    token->value = value;
    token->type = type;
    return (token);
}

t_token_type find_type(char c)
{
    size_t i;
    char *str;
    t_token_type type;

    i = 0;
    type = literal;
    while (g_tab_token[i].value)
    {
        str = g_tab_token[i].value;
        if (str[0] == c)
        {
            type = g_tab_token[i].type;
            return (type);
        }
        i++;
    }
    return (type);
}

void    parsing(char *user_input)
{
    char *new;
    size_t i;
    size_t size;

    i = 0;
    size = ft_strlen(user_input);
    while (i < size)
    {
        new = ft_strndup(user_input + i, 1);
        tokenizer(new);
        free(new);
        // ne pas oublier de free new
        i++;
    }
    concat_tokens_all();
    concat_tokens_quotes();
}

void    tokenizer(char *input)
{
    t_list          *new;
    char            *value;
    t_token         *token;
    t_token_type    type;

    value = ft_strdup(input);
    if (!value)
        exit(-1);
    type = find_type(value[0]);
    token = create_token(value, type);
    if (!(new = ft_lstnew(token)))
        exit (-1);
    ft_lstadd_back(&g_sys_infos.list_input, new);
}

t_token_type get_token_type(t_token *token)
{
    //printf("%i\n", token->type);
    return (token->type);
}

void *get_token_value(t_token *token)
{
    return (token->value);
}

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

void    del_node(t_list *node)
{
    node->content = NULL;
	node->next = NULL;
}

void    concat_tokens_quotes()
{
    checking_if_quotes_even();
}

void    concat_tokens_all()
{
    t_list *tmp_list;
    t_list *begin;

    begin = g_sys_infos.list_input;

    while (g_sys_infos.list_input != NULL && g_sys_infos.list_input->next != NULL)
    {
        //printf("act : %s\n", g_sys_infos.list_input->content->value);
        if (get_token_type(g_sys_infos.list_input->content) == get_token_type(g_sys_infos.list_input->next->content))
        {
            g_sys_infos.list_input->content = join_two_tokens(g_sys_infos.list_input->content, g_sys_infos.list_input->next->content);
            //printf("%s\n", g_sys_infos.list_input->content->value);
            tmp_list = g_sys_infos.list_input->next->next;
            // printf("%s\n", tmp_list->content->value);
            del_node(g_sys_infos.list_input->next);
            g_sys_infos.list_input->next->content = tmp_list->content;
            g_sys_infos.list_input->next->next = tmp_list->next;
            //printf("%s\n", g_sys_infos.list_input->next->content->value);
            //printf("%p\n", g_sys_infos.list_input->next->next);
        }
        else// if (g_sys_infos.list_input->next != NULL)
        {
            //printf("'%s' -> '%s'\n", g_sys_infos.list_input->content->value, g_sys_infos.list_input->next->content->value);
            g_sys_infos.list_input = g_sys_infos.list_input->next;
        }
        //g_sys_infos.list_input = tmp_sys_infos->list_input->next;
    }
    g_sys_infos.list_input = begin;
    //printf("Test\n");
}
/*
1: T 2: E 3: S 4: T
1: TE 2: E 3: S 4: T
1: TE 2: S 3: T
*/
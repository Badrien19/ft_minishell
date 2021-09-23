#include "includes/ft_minishell.h"

static	t_token			g_tab_token[] = {
	{"|", pipeline},
	{"<", simple_redir_left},
	{">", simple_redir_right},
    {"<<", double_redir_left},
    {">>", double_redir_right},
	{";", semicolon},
	{"\"", double_quote},
	{"'", single_quote},
	{"\\", backslash},
	{"\f", space},
	{"\n", line_return},
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
    //printf("New Token ! ('%s' - %i)\n", (char *)token->value, token->type);
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

t_bool    parsing(char *user_input)
{
    char *new;
    size_t i;
    size_t size;

    i = 0;
    size = ft_strlen(user_input);
    if (size == 0)
        return (False);
    while (i < size)
    {
        new = ft_strndup(user_input + i, 1);
        tokenizer(new);
        free(new);
        i++;
    }
    concat_tokens_same_type();
    //print_current_chain(); DEBUG
    printf("__TEST1__\n");
    concat_tokens_var();
    printf("__TEST2__\n");
    if (concat_tokens_quotes() == False)
        return (False);
    return (True);
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
    ft_lstadd_back(&g_minishell.list_input, new);
}

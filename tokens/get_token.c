#include "../includes/ft_minishell.h"

t_token_type get_token_type(t_token *token)
{
    //printf("%i\n", token->type);
    return (token->type);
}

void *get_token_value(t_token *token)
{
    return (token->value);
}
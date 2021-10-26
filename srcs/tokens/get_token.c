#include "../../includes/ft_minishell.h"

t_token_type get_token_type(t_token *token)
{
    if (!token)
        return (none);
    return (token->type);
}

void *get_token_value(t_token *token)
{
    if (!token)
        return (NULL);
    return (token->value);
}
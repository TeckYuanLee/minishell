#include "minishell.h"

t_err	get_env_key(const char *str, char **return_key)
{
	int		i;

	*return_key = NULL;
	i = 0;
	if (ft_isdigit(*str))
		return (KEY_ERR);
	while (allowed_char(str[i], "$()<>'/\\;=.\0") && !ft_isspace(str[i]))
		i++;
	*return_key = ft_calloc(i + 1, 1);
	if (!*return_key)
		return (MALLOC_FAIL);
	ft_strlcpy(*return_key, str, i + 1);
	return (NO_ERROR);
}

t_bool	allowed_char(int c, char *not_allowed)
{
	if (ft_strchr(not_allowed, c))
		return (FALSE);
	return (TRUE);
}

void	add_to_tokenlist(t_token_list **head, t_token_list *new)
{
	t_token_list	*node;

	if (!*head)
		*head = new;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		new->prev = node;
		node->next = new;
	}
}

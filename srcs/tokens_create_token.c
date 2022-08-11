#include "minishell.h"

//  insert new token between current token and next token /////
void	insert_token_after(t_token *list, t_token *new)
{
	if (!list)
		printf(BHRED "[insert_token_after] empty list?!\n" BHWHT);
	else if (!new)
		printf(BHRED "[insert_token_after] empty (new)list?!\n" BHWHT);
	else
	{
		new->next = list->next;
		if (list->next)
			list->next->prev = new;
		list->next = new;
		new->prev = list;
	}
}

//  replace current token with new token: head or not /////
t_err	insert_tokens(t_token **head, char *key, char *value, char *data)
{
	char	*data_dup;
	t_err	err;

	data_dup = ft_strdup(data);
	if (!data_dup)
		return (MALLOC_FAIL);
	if ((*head)->prev)
		err = do_normalstuff(*head, key, value, data_dup);
	else
		err = do_headstuff(head, key, value, data_dup);
	free(data_dup);
	return (err);
}

//	add created token to the tokenlist /////
void	add_to_tokenlist(t_token **head, t_token *new)
{
	t_token	*node;

	node = NULL;
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

//	create token and add to tokenlist /////
t_err	add_new_token(t_token	**head, t_token_t type, char *data)
{
	t_token	*new;

	new = create_token(type, data);
	if (!new)
		return (MALLOC_FAIL);
	add_to_tokenlist(head, new);
	return (NO_ERROR);
}

//	create and add a new token /////
t_token	*create_token(t_token_t type, char *data)
{
	static int	id = 0;
	t_token		*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (new_token)
	{
		new_token->type = type;
		new_token->data = data;
		new_token->id = id;
		new_token->next = NULL;
		new_token->prev = NULL;
		id++;
	}
	return (new_token);
}

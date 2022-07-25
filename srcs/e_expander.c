#include "minishell"

t_err	rm_token_type(t_token_list **list, t_envi *info, t_token_type type)
{
	t_token_list	*node;
	t_token_list	*temp;

	(void)info;
	node = *list;
	while (node)
	{
		temp = node->next;
		if (node->type == type)
		{
			if (node->prev)
				cut_token(node);
			else
				cut_head_token(list);
		}
		node = temp;
	}
	return (NO_ERROR);
}

t_err	word_join(t_token_list **list, t_envi *info, t_token_type type)
{
	t_err			rv;
	t_token_list	*node;

	(void)info;
	(void)type;
	node = *list;
	if (!node)
		return (printf("[word_join] Empty token_list?\n"));
	while (node->next)
	{
		if (node->type == TOK_WORD && node->next->type == TOK_WORD)
		{
			if (node->prev == NULL)
				rv = join_head_token(list, TOK_WORD);
			else
				rv = join_token(node, TOK_WORD);
			if (rv == MALLOC_FAIL)
				return (MALLOC_FAIL);
			node = *list;
		}
		else
			node = node->next;
	}
	return (NO_ERROR);
}

t_err	expand_dollars(t_token_list **list, t_envi *info, t_token_type type)
{
	char			*key;
	t_token_list	*node;
	t_token_list	*temp;
	t_err			rv;

	(void)type;
	key = NULL;
	node = *list;
	while (node)
	{
		if (node->type == 4 && node->next && node->next->type == TOK_WORD)
		{
			temp = node->next->next;
			if (node->prev)
				rv = prep_expand_d(&node, info, key);
			else
				rv = prep_expand_d(list, info, key);
			if (rv == MALLOC_FAIL)
				return (MALLOC_FAIL);
			node = temp;
		}
		else
			node = node->next;
	}
	return (NO_ERROR);
}

t_err	quotes_to_words(t_token_list **list, t_envi *info, t_token_type type)
{
	t_token_list	*node;

	(void)info;
	(void)type;
	node = *list;
	if (!node)
		return (EMPTY);
	while (node)
	{
		if (node->type == TOK_QUOTE || node->type == TOK_DQUOTE)
			node->type = TOK_WORD;
		node = node->next;
	}
	return (NO_ERROR);
}

t_err	rm_double_tokens(t_token_list **list, t_envi *info, t_token_type type)
{
	t_token_list	*node;
	t_token_list	*temp;

	(void)info;
	node = *list;
	if (!node)
		return (EMPTY);
	while (node && node->next)
	{
		temp = node->next;
		if (node->type == type && node->next->type == type)
		{
			if (node->prev)
				cut_token(node);
			else
				cut_head_token(list);
		}
		node = temp;
	}
	return (NO_ERROR);
}

t_err	expander(char *line, t_curr_input *input, t_envi *info)
{
	int							i;
	t_err						rv;
	t_token_list				**list;
	static t_expander_funptr	expander_funptr[4] = {
	[0] = rm_double_tokens,
	[1] = quotes_to_words,
	[2] = expand_dollars,
	[3] = word_join
	};

	(void)line;
	i = 0;
	rv = NO_ERROR;
	list = &input->lexer;
	while (rv == NO_ERROR && i < 4)
	{
		if (!*list)
			return (EMPTY);
		rv = expander_funptr[i](list, info, TOK_DOLLAR);
		i++;
	}
	if (rv != NO_ERROR)
		return (rv);
	rm_token_type(list, info, TOK_SPACE);
	return (NO_ERROR);
}

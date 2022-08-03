#include "minishell.h"

//	join words for current token and next token(s) /////
t_err	word_join(t_token **list)
{
	t_err	err;
	t_token	*node;

	node = *list;
	if (!node)
		return (EMPTY);
	while (node->next)
	{
		if (node->type == TOK_WORD && node->next->type == TOK_WORD)
		{
			if (node->prev == NULL)
				err = join_head_token(list, TOK_WORD);
			else
				err = join_token(node, TOK_WORD);
			if (err == MALLOC_FAIL)
				return (MALLOC_FAIL);
			node = *list;
		}
		else
			node = node->next;
	}
	return (NO_ERROR);
}

//	search list for $ and words, expand this combination /////
t_err	expand_dollars(t_token **list, t_env *info)
{
	char	*key;
	t_token	*node;
	t_token	*temp;
	t_err	err;

	key = NULL;
	node = *list;
	while (node)
	{
		if (node->type == 4 && node->next && node->next->type == TOK_WORD)
		{
			temp = node->next->next;
			if (node->prev)
				err = prep_expand_d(&node, info, key);
			else
				err = prep_expand_d(list, info, key);
			if (err == MALLOC_FAIL)
				return (MALLOC_FAIL);
			node = temp;
		}
		else
			node = node->next;
	}
	return (NO_ERROR);
}

//	change token type from quotes to words /////
t_err	quotes_to_words(t_token **list)
{
	t_token	*node;

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

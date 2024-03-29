/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:28:45 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:28:45 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				err = join_token_head(list, TOK_WORD);
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
t_err	expand_dollars_words(t_token **list, t_env *ms_env)
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
				err = expand_dollars(&node, ms_env, key);
			else
				err = expand_dollars(list, ms_env, key);
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

//	expand tokens /////
t_err	expander(t_input *input, t_env *ms_env)
{
	t_err	err;
	t_token	**list;

	list = &input->lexer;
	if (!*list)
		return (EMPTY);
	err = rm_double_tokens(list, TOK_DOLLAR);
	if (err == NO_ERROR)
		err = quotes_to_words(list);
	if (err == NO_ERROR)
		err = expand_dollars_words(list, ms_env);
	if (err == NO_ERROR)
		err = word_join(list);
	if (err == NO_ERROR)
		return (rm_token_type(list, TOK_SPACE));
	return (err);
}

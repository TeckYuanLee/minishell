/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_create_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:30:42 by telee             #+#    #+#             */
/*   Updated: 2022/08/19 10:34:30 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  replace current token with new token: head or normal
t_err	insert_tokens(t_token **head, char *key, char *value, char *data)
{
	char	*data_dup;
	t_err	err;

	data_dup = ft_strdup(data);
	if (!data_dup)
		return (MALLOC_FAIL);
	if ((*head)->prev)
		err = sub_token(*head, key, value, data_dup);
	else
		err = sub_token_head(head, key, value, data_dup);
	free(data_dup);
	return (err);
}

//	add created token to the tokenlist
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

//	create token and add to tokenlist
t_err	add_new_token(t_token	**head, t_token_t type, char *data)
{
	t_token	*new;

	new = create_token(type, data);
	if (!new)
		return (MALLOC_FAIL);
	add_to_tokenlist(head, new);
	return (NO_ERROR);
}

//	create and initialize new token
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
		id++;
	}
	return (new_token);
}

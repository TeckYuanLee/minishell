/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:25:06 by telee             #+#    #+#             */
/*   Updated: 2022/07/25 09:25:06 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	treat single dollar as word token
t_err	add_dollar_sign(t_token	**list)
{
	char	*str;
	t_token	*new_token;

	str = ft_strdup("$");
	if (!str)
		return (MALLOC_FAIL);
	new_token = create_token(TOK_WORD, str);
	if (!new_token)
	{
		free (str);
		return (MALLOC_FAIL);
	}
	add_to_tokenlist(list, new_token);
	return (NO_ERROR);
}

//	add new token to the tokenlist
t_err	add_new_token(t_token	**head, t_token_type type, char *data)
{
	t_token	*new;

	new = create_token(type, data);
	if (!new)
		return (MALLOC_FAIL);
	add_to_tokenlist(head, new);
	return (NO_ERROR);
}

//	create and add a new token
t_token	*create_token(t_token_type type, char *data)
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

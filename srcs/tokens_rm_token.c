/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_rm_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:31:46 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:31:47 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  replace current/first token with new token
void	replace_token(t_token *list, t_token *new)
{
	if (list->prev)
	{
		new->next = list->next;
		if (new->next)
			list->next->prev = new;
		new->prev = list->prev;
		if (new->prev)
			list->prev->next = new;
		del_token(list);
	}
	else
	{
		if ((list)->next)
		{
			new->next = (list)->next;
			(list)->next->prev = new;
		}
		del_token(list);
		list = new;
	}
}

//	remove space tokens /////
t_err	rm_token_type(t_token **list, t_token_t type)
{
	t_token	*node;
	t_token	*temp;

	node = *list;
	while (node)
	{
		temp = node->next;
		if (node->type == type)
			remove_token(node);
		node = temp;
	}
	return (NO_ERROR);
}

//	remove duplicated dollar tokens /////
t_err	rm_double_tokens(t_token **list, t_token_t type)
{
	t_token	*node;
	t_token	*temp;

	node = *list;
	if (!node)
		return (EMPTY);
	while (node && node->next)
	{
		temp = node->next;
		if (node->type == type && node->next->type == type)
			remove_token(node);
		node = temp;
	}
	return (NO_ERROR);
}

//  delete the current token from list /////
void	del_token(t_token *list)
{
	if (!list)
		return ((void)printf(BHRED "[del_token] (Null) token!!\n" BHWHT));
	free(list->data);
	free (list);
}

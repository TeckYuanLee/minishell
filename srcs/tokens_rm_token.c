/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_rm_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:31:46 by telee             #+#    #+#             */
/*   Updated: 2022/08/24 17:14:29 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_token_head(t_token **head, t_token *new)
{	
	if ((*head)->next)
	{
		new->next = (*head)->next;
		(*head)->next->prev = new;
	}
	del_token(*head);
	*head = new;
}

void	replace_token(t_token *list, t_token *new)
{
	new->next = list->next;
	if (list->next)
		list->next->prev = new;
	new->prev = list->prev;
	if (list->prev)
		list->prev->next = new;
	del_token(list);
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
		{
			if (node->prev)
				remove_token(node);
			else
				remove_token_head(list);
		}
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
		{
			if (node->prev)
				remove_token(node);
			else
				remove_token_head(list);
		}
		node = temp;
	}
	return (NO_ERROR);
}

//  delete the current token from list /////
void	del_token(t_token *list)
{
	char	**str;

	if (!list)
		return ;
	str = &list->data;
	free(*str);
	*str = NULL;
	free (list);
}

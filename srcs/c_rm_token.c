#include "minishell.h"

//  replace current token with new token /////
void	replace_token(t_token *list, t_token *new)
{
	if (!list)
		return ((void)printf(BHRED "[replace_token] no token_list..\n" BHWHT));
	if (!list->prev)
		return ((void)printf(BHRED "[replace_token] no prev in \
			token_list..\n" BHWHT));
	new->next = list->next;
	if (new->next)
		list->next->prev = new;
	new->prev = list->prev;
	if (new->prev)
		list->prev->next = new;
	del_token(list);
}

//  replace first token with new token /////
void	replace_head_token(t_token **head, t_token *new)
{
	if (!*head)
		return ((void)printf(BHRED "[replace_head_token] no head..\n" BHWHT));
	if ((*head)->prev)
		return ((void)printf(BHRED "[replace_head_token] not a head?\n" BHWHT));
	if ((*head)->next)
	{
		new->next = (*head)->next;
		(*head)->next->prev = new;
	}
	del_token(*head);
	*head = new;
}

//	remove space tokens /////
t_err	rm_token_type(t_token **list, t_token_t type)
{
	t_token	*node;
	t_token	*temp;

	node = *list;
	// printf("%d\n", node->type);
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
				cut_token(node);
			else
				cut_head_token(list);
		}
		node = temp;
	}
	return (NO_ERROR);
}

//  delete the current token from list /////
void	del_token(t_token *list)
{
	if (!list)
		return ((void)printf(BHRED "[del_token] (Null) token!!\n" BHWHT));
	ft_free_str(&list->data);
	free (list);
}

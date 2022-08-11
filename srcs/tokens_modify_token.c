#include "minishell.h"

//  create new token with new string /////
t_err	insert_full_string(t_token **head, char *key, char *data)
{
	int		len;
	char	*str;
	t_token	*var_token;

	free(key);
	len = ft_strlen(data);
	str = ft_calloc(len + 2, 1);
	if (!str)
		return (MALLOC_FAIL);
	create_full_string(&str, data, len);
	var_token = create_token(TOK_WORD, str);
	if (!var_token)
	{
		free(str);
		return (MALLOC_FAIL);
	}
	if ((*head)->prev)
		replace_token(*head, var_token);
	else
		replace_head_token(head, var_token);
	return (NO_ERROR);
}

//  create new token with current and next token /////
t_err	join_token(t_token *list, t_token_t resulting_type)
{
	t_token	*new_token;
	char	*new_data;

	new_data = ft_strjoin(list->data, list->next->data);
	if (!new_data)
		return (MALLOC_FAIL);
	new_token = create_token(resulting_type, new_data);
	if (!new_token)
	{
		free (new_data);
		return (MALLOC_FAIL);
	}
	new_token->next = list->next->next;
	if (new_token->next)
		list->next->next->prev = new_token;
	new_token->prev = list->prev;
	list->prev->next = new_token;
	del_token(list->next);
	del_token(list);
	return (NO_ERROR);
}

//  create new token with first and second token /////
t_err	join_head_token(t_token **list, t_token_t resulting_type)
{
	t_token	*new_token;
	char	*new_data;

	new_data = ft_strjoin((*list)->data, (*list)->next->data);
	if (!new_data)
		return (MALLOC_FAIL);
	new_token = create_token(resulting_type, new_data);
	if (!new_token)
	{
		free (new_data);
		return (MALLOC_FAIL);
	}
	new_token->next = (*list)->next->next;
	if (new_token->next)
		(*list)->next->next->prev = new_token;
	del_token((*list)->next);
	del_token(*list);
	*list = new_token;
	return (NO_ERROR);
}

//  remove current token from list /////
void	cut_token(t_token *list)
{
	if (!list)
		return ((void)printf(BHRED "[cut_token] no token_list..\n" BHWHT));
	if (!list->prev)
		return ((void)printf(BHRED "[cut_token] no prev in token_list..\n" BHWHT));
	if (list->next)
		list->next->prev = list->prev;
	list->prev->next = list->next;
	del_token(list);
}

//  remove the first token on the list /////
void	cut_head_token(t_token **head)
{
	t_token	*new_head;

	if (!*head)
		return ((void)printf(BHRED "[cut_head_token] empty list.\n" BHWHT));
	if ((*head)->prev)
		return ((void)printf(BHRED "[cut_head_token] this is no head..\n" BHWHT));
	if ((*head)->next)
	{
		new_head = (*head)->next;
		new_head->prev = NULL;
		del_token(*head);
		*head = new_head;
	}
	else
	{
		del_token(*head);
		*head = NULL;
	}
}

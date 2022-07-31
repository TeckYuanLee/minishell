#include "minishell.h"

//  expand $ and words
t_err	expand_d(t_token **head, t_env *info, char *key, char *data)
{
	char    *value;

	if (get_env_key(data, &key) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ft_strncmp(data, "?", 1) == 0)
		value = ft_itoa(info->exitcode);
	else if (!allowed_char(data[0], "/=."))
		return (insert_full_string(head, key, data));
	else if (get_env_value(info->ms_envp, key, &value) == MALLOC_FAIL)
	{
		free(key);
		return (MALLOC_FAIL);
	}
	if (value)
		return (insert_tokens(head, key, value, data));
	if (expand_d_tailbit(head, key, data) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	free (key);
	return (NO_ERROR);
}

//  preparation to expand $ and words
t_err	prep_expand_d(t_token **head, t_env *info, char *key)
{
	t_token	*next;
	char	*data;

	data = (*head)->next->data;
	next = (*head)->next;
	if ((*head)->prev)
	{
		cut_token(*head);
		return (expand_d(&next, info, key, data));
	}	
	cut_head_token(head);
	return (expand_d(head, info, key, data));
}

//  create new token with first and second token
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

//  create new token with current and next token
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

//  remove current token from list
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

//  remove the first token on the list
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

#include "minishell.h"

//  create new string /////
void	create_full_string(char **str, char *data, int len)
{
	(*str)[0] = '$';
	while (len >= 0)
	{
		(*str)[len + 1] = data[len];
		len--;
	}
}

//  create the remaining part of the token /////
t_token	*create_tailpart(char *key, char *data)
{
	char	*str;

	str = ft_strdup(data + ft_strlen(key));
	if (!str)
		return (NULL);
	return (create_token(TOK_WORD, str));
}

//  create new token to replace current token /////
t_err	do_normalstuff(t_token *list, char *key, char *value, char *data)
{
	t_token	*var_token;
	t_token	*temp;

	var_token = create_token(TOK_WORD, value);
	if (!var_token)
	{
		free(key);
		free(value);
		return (MALLOC_FAIL);
	}
	temp = var_token;
	replace_token(list, var_token);
	if (ft_strlen(data) > ft_strlen(key))
	{
		var_token = create_tailpart(key, data);
		if (!var_token)
			return (MALLOC_FAIL);
		insert_token_after(temp, var_token);
	}
	free (key);
	return (NO_ERROR);
}

//  create new token to replace head token /////
t_err	do_headstuff(t_token **head, char *key, char *value, char *data)
{
	t_token	*var_token;
	t_token	*temp;

	var_token = create_token(TOK_WORD, value);
	if (!var_token)
	{
		free(value);
		return (MALLOC_FAIL);
	}
	temp = var_token;
	replace_head_token(head, var_token);
	if (ft_strlen(data) > ft_strlen(key))
	{
		var_token = create_tailpart(key, data);
		if (!var_token)
			return (MALLOC_FAIL);
		insert_token_after(temp, var_token);
	}
	free(key);
	return (NO_ERROR);
}

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

//  insert new token between current token and next token /////
void	insert_token_after(t_token *list, t_token *new)
{
	if (!list)
		printf(BHRED "[insert_token_after] empty list?!\n" BHWHT);
	else if (!new)
		printf(BHRED "[insert_token_after] empty (new)list?!\n" BHWHT);
	else
	{
		new->next = list->next;
		if (list->next)
			list->next->prev = new;
		list->next = new;
		new->prev = list;
	}
}

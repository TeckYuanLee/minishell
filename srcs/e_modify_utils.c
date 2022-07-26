#include "minishell.h"

//  delete the current token
void	del_token(t_token *list)
{
	if (!list)
		return (printf(BHRED "[del_token] (Null) token!!\n" BHWHT));
	ft_free_str(&list->data);
	free (list);
}

//  create new token with new string
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

//  insert new token before current token
t_err	insert_tokens(t_token **head, char *key, char *value, char *data)
{
	char	*data_dup;
	t_err	err;

	data_dup = ft_strdup(data);
	if (!data_dup)
		return (MALLOC_FAIL);
	if ((*head)->prev)
		err = do_normalstuff(*head, key, value, data_dup);
	else
		err = do_headstuff(head, key, value, data_dup);
	free(data_dup);
	return (err);
}

//  create remaining part of the token
t_err	expand_d_tailbit(t_token **head, char *key, char *data)
{
	t_token	*var_token;

	if (ft_strlen(data) > ft_strlen(key))
	{
		var_token = create_tailpart(key, data);
		if (!var_token)
		{
			free (key);
			return (MALLOC_FAIL);
		}
		replace_token(*head, var_token);
	}
	else
	{
		if ((*head)->prev)
			cut_token(*head);
		else
			cut_head_token(head);
	}
	return (NO_ERROR);
}
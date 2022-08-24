/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:30:47 by telee             #+#    #+#             */
/*   Updated: 2022/08/24 17:32:30 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  create remaining part of the token else remove token /////
t_err	expand_dollars_tail(t_token **head, char *key, char *data)
{
	t_token	*var_token;

	if (ft_strlen(data) > ft_strlen(key))
	{
		var_token = token_tail(key, data);
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
			remove_token(*head);
		else
			remove_token_head(head);
	}
	return (NO_ERROR);
}

//  expand $ and words /////
t_err	expand_d_utils(t_token **head, t_env *ms_env, char *key, char *data)
{
	char	*value;

	if (get_env_key(data, &key) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ft_strncmp(data, "?", 1) == 0)
		value = ft_itoa(ms_env->exitcode);
	else if (!allowed_char(data[0], "/=."))
		return (newstr_token(head, key, data));
	else if (get_env_value(ms_env->item, key, &value) == MALLOC_FAIL)
	{
		free(key);
		return (MALLOC_FAIL);
	}
	if (value)
		return (insert_tokens(head, key, value, data));
	if (expand_dollars_tail(head, key, data) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	free (key);
	return (NO_ERROR);
}

//  preparation to expand $ and words /////
t_err	expand_dollars(t_token **head, t_env *ms_env, char *key)
{
	t_token	*next;
	char	*data;

	data = (*head)->next->data;
	next = (*head)->next;
	if ((*head)->prev)
	{
		remove_token(*head);
		return (expand_d_utils(&next, ms_env, key, data));
	}	
	remove_token_head(head);
	return (expand_d_utils(head, ms_env, key, data));
}

//	treat single dollar as word token /////
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

//	check for dollars in readline /////
t_err	dollars(char *input, int *i, t_token **list)
{
	t_token	*new_token;

	(*i)++;
	if (input[1] == '\0' || ft_isspace(input[1]))
		return (add_dollar_sign(list));
	if (ft_isdigit(input[1]))
	{
		(*i)++;
		return (NO_ERROR);
	}
	if (input[1] == '?')
	{
		(*i)++;
		return (exitcode_token(input, i, list));
	}
	new_token = create_token(TOK_DOLLAR, NULL);
	if (new_token)
		add_to_tokenlist(list, new_token);
	if (!new_token || !*list)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

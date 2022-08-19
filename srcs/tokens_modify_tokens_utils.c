/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_modify_tokens_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:31:35 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:31:35 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	handle '$?'
t_err	exitcode_token(const char *dquote, int *j, t_token **list)
{
	char	*question;

	(void)dquote;
	(void)j;
	question = ft_strdup("?");
	if (!question)
		return (MALLOC_FAIL);
	if (add_new_token(list, TOK_DOLLAR, NULL) == MALLOC_FAIL)
	{
		free(question);
		return (MALLOC_FAIL);
	}
	if (add_new_token(list, TOK_WORD, question) == MALLOC_FAIL)
	{
		free(question);
		return (MALLOC_FAIL);
	}
	return (NO_ERROR);
}

//  create the remaining part of the token
t_token	*token_tail(char *key, char *data)
{
	char	*str;

	str = ft_strdup(data + ft_strlen(key));
	if (!str)
		return (NULL);
	return (create_token(TOK_WORD, str));
}

//  create new token to replace current token
t_err	sub_token(t_token *list, char *key, char *value, char *data)
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
		var_token = token_tail(key, data);
		if (!var_token)
			return (MALLOC_FAIL);
		var_token->next = temp->next;
		if (temp->next)
			temp->next->prev = var_token;
		temp->next = var_token;
		var_token->prev = temp;
	}
	free (key);
	return (NO_ERROR);
}

//  create new token to replace head token
t_err	sub_token_head(t_token **head, char *key, char *value, char *data)
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
	replace_token_head(head, var_token);
	if (ft_strlen(data) > ft_strlen(key))
	{
		var_token = token_tail(key, data);
		if (!var_token)
			return (MALLOC_FAIL);
		var_token->next = temp->next;
		if (temp->next)
			temp->next->prev = var_token;
		temp->next = var_token;
		var_token->prev = temp;
	}
	free(key);
	return (NO_ERROR);
}

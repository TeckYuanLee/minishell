/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:25:15 by telee             #+#    #+#             */
/*   Updated: 2022/07/25 09:25:15 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	handle '$?' /////
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
		var_token = create_tailpart(key, data);
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
t_err	sub_head_token(t_token **head, char *key, char *value, char *data)
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
		var_token->next = temp->next;
		if (temp->next)
			temp->next->prev = var_token;
		temp->next = var_token;
		var_token->prev = temp;
	}
	free(key);
	return (NO_ERROR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:24:45 by telee             #+#    #+#             */
/*   Updated: 2022/07/25 09:24:45 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	check for spaces in readline
t_err	spaces(char *input, int *i, t_token **list)
{
	t_token	*new_token;
	int		j;

	j = 0;
	while (ft_isspace(input[j]))
		j++;
	new_token = create_token(TOK_SPACE, NULL);
	if (!new_token)
		return (MALLOC_FAIL);
	add_to_tokenlist(list, new_token);
	*i += j;
	return (NO_ERROR);
}

//	check for words and save them for parser
t_err	words(char *input, int *i, t_token **list)
{
	t_token	*new_token;
	char	*word;

	word = save_word(input);
	if (!word)
		return (MALLOC_FAIL);
	new_token = create_token(TOK_WORD, word);
	if (!new_token)
	{
		free (word);
		return (MALLOC_FAIL);
	}
	add_to_tokenlist(list, new_token);
	*i += ft_strlen(new_token->data);
	return (NO_ERROR);
}

//	check for single and double quotes in readline
t_err	quotes(char *input, int *i, t_token **list)
{
	t_token	*new_token;
	char	*quote;
	t_err	err;

	err = save_quote(input + 1, &quote, input);
	if (err != NO_ERROR)
		return (err);
	*i += ft_strlen(quote) + 2;
	if (*input == '"')
	{
		if (ft_strchr(quote, '$'))
			return (expand_d_quote(quote, list));
		new_token = create_token(TOK_DQUOTE, quote);
	}
	else
		new_token = create_token(TOK_QUOTE, quote);
	if (!new_token)
	{
		free (quote);
		return (MALLOC_FAIL);
	}
	add_to_tokenlist(list, new_token);
	return (NO_ERROR);
}

//	check for pipes and dollars in readline
t_err	pipes_dollars(char *input, int *i, t_token **list)
{
	t_token	*new_token;

	(*i)++;
	new_token = NULL;
	if (*input == '|')
	{
		if (input[1] == '|')
			return (syntax_err_lexer((char)DOUBLE_PIPE));
		new_token = create_token(TOK_PIPE, NULL);
	}
	else if (*input == '$')
	{
		if (input[1] == '\0' || ft_isspace(input[1]))
			return (add_dollar_sign(list));
		if (ft_isdigit(input[1]))
			return ((*i)++ | NO_ERROR);
		if (input[1] == '?')
			return (exitcode_token(input, ++i, list));
		new_token = create_token(TOK_DOLLAR, NULL);
	}
	if (new_token)
		add_to_tokenlist(list, new_token);
	if (!new_token || !*list)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

//	check for left and right angular brackets in readline
t_err	lnr_angles(char *input, int *i, t_token **list)
{
	t_token	*new_token;

	if (*input == '<' && input[1] == '<')
	{
		new_token = create_token(TOK_HERE_DOC, NULL);
		(*i)++;
	}
	else if (*input == '<')
		new_token = create_token(TOK_REDIR_IN, NULL);
	else if (*input == '>' && input[1] == '>')
	{
		new_token = create_token(TOK_APPEND, NULL);
		(*i)++;
	}
	else
		new_token = create_token(TOK_REDIR_OUT, NULL);
	(*i)++;
	if (new_token)
		add_to_tokenlist(list, new_token);
	if (!new_token || !*list)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

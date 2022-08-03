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

//	check for spaces in readline /////
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

//	check for words and save them for parser /////
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

//	check for pipes in readline /////
t_err	pipes(char *input, int *i, t_token **list)
{
	t_token	*new_token;

	(*i)++;
	if (input[1] == '|')
		return (syntax_err_lexer((char)DOUBLE_PIPE));
	new_token = create_token(TOK_PIPE, NULL);
	if (new_token)
		add_to_tokenlist(list, new_token);
	if (!new_token || !*list)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

//	check for left and right angular brackets in readline /////
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

//	tokenize symbols /////
t_err	tokenize(char *input, int *i, t_token **list)
{
	if (*input == '<' || *input == '>')
		return (lnr_angles(input, i, list));
	else if (*input == '|')
		return (pipes(input, i, list));
	else if (*input == '$')
		return (dollars(input, i, list));
	else if (*input == '\'' || *input == '"')
		return (quotes(input, i, list));
	else
		return (words(input, i, list));
}

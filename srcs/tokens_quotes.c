/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:31:42 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:31:42 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	check for single and double quotes in readline /////
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
		{
			err = expand_dquote_dollars(quote, list);
			free (quote);
			return (err);
		}
		new_token = create_token(TOK_DQUOTE, quote);
	}
	else
		new_token = create_token(TOK_QUOTE, quote);
	if (rm_tokens(new_token, &quote) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	add_to_tokenlist(list, new_token);
	return (NO_ERROR);
}

//	save content within quotes to create token /////
t_err	save_quote(const char *line, char **quote, char *input)
{
	int	i;

	i = 0;
	if (*input == '\'')
		while (allowed_char(line[i], "'\0"))
			i++;
	else if (*input == '"')
		while (allowed_char(line[i], "\"\0"))
			i++;
	if (!(line[i] == '\'' || line[i] == '"'))
	{
		ft_putstr_fd("minishell: open-ended ", 2);
		ft_putstr_fd("quote (unsupported)\n", 2);
		return (SYNTAX_ERR);
	}
	*quote = malloc(i + 1);
	if (!*quote)
		return (MALLOC_FAIL);
	ft_strlcpy(*quote, line, i + 1);
	return (NO_ERROR);
}

//	handle dollar sign during double quote /////
t_err	dquote_dollars(const char *dquote, int *j, t_token **list)
{
	char	*key;

	(*j)++;
	if (dquote[*j] == '\0' || ft_isspace(dquote[*j]))
		return (add_dollar_sign(list));
	if (ft_isdigit(dquote[*j]))
	{
		(*j)++;
		return (NO_ERROR);
	}
	if (dquote[*j] == '?')
	{
		(*j)++;
		return (exitcode_token(dquote, j, list));
	}
	if (get_env_key(&dquote[*j], &key) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (key)
	{
		add_new_token(list, TOK_DOLLAR, NULL);
		add_new_token(list, TOK_WORD, key);
		*j += ft_strlen(key);
	}
	return (NO_ERROR);
}

//	expand double quote when there is a dollar sign /////
t_err	expand_dquote_dollars(const char *dquote, t_token **list)
{
	int		j;
	char	*word;

	while (*dquote)
	{
		j = 0;
		while (dquote[j] && dquote[j] != '$')
			j++;
		if (j > 0)
		{
			word = ft_substr(dquote, 0, j);
			if (!word)
				return (MALLOC_FAIL);
			if (add_new_token(list, TOK_QUOTE, word) == MALLOC_FAIL)
			{
				free (word);
				return (MALLOC_FAIL);
			}
		}
		if (dquote[j] == '$')
			if (dquote_dollars(dquote, &j, list) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		dquote += j;
	}
	return (NO_ERROR);
}

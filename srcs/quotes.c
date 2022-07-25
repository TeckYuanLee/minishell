/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:25:09 by telee             #+#    #+#             */
/*   Updated: 2022/07/25 09:25:09 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd("minishell: syntax error open-ended ", 2);
		ft_putstr_fd("quote (unsupported)\n", 2);
		return (SYNTAX_ERR);
	}
	*quote = malloc(i + 1);
	if (!*quote)
		return (MALLOC_FAIL);
	ft_strlcpy(*quote, line, i + 1);
	return (NO_ERROR);
}

t_err	expand_dquote(const char *dquote, t_token **list)
{
	int		j;

	while (*dquote)
	{
		j = 0;
		while (dquote[j] && dquote[j] != '$')
			j++;
		if (j > 0)
			if (put_dquote_token(dquote, list, j) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		if (dquote[j] == '$')
			if (d_quote_dollars(dquote, &j, list) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		dquote += j;
	}
	return (NO_ERROR);
}

t_err	put_dquote_token(const char *dquote, t_token **list, int j)
{
	char	*word;

	word = ft_substr(dquote, 0, j);
	if (!word)
		return (MALLOC_FAIL);
	if (add_new_token(list, TOK_QUOTE, word) == MALLOC_FAIL)
	{
		free (word);
		return (MALLOC_FAIL);
	}
	return (NO_ERROR);
}

t_err	d_quote_dollars(const char *dquote, int *j, t_token **list)
{
	char	*key;

	(*j)++;
	if (dquote[*j] == '\0' || ft_isspace(dquote[*j]))
		return (add_dollar_sign(list));
	else if (ft_isdigit(dquote[*j]))
		return ((*j)++ || NO_ERROR);
	else if (dquote[*j] == '?')
		return (exitcode_token(dquote, ++j, list) == MALLOC_FAIL);
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

//	copy word literal
char	*save_word(const char *input)
{
	char	*word;
	int		i;

	i = 0;
	while (allowed_char(input[i], "<>|$';\"\\[]{}()")
		&& !ft_isspace(input[i]))
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, input, i + 1);
	return (word);
}

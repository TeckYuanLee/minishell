#include "minishell.h"

t_err	save_quote(const char *line, char **quote, char *input)
{
	int		i;

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

t_err	expand_dquote(const char *dquote, t_token_list **list)
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
			if (dquote_dollar_token(dquote, &j, list) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		dquote += j;
	}
	return (NO_ERROR);
}

t_err	put_dquote_token(const char *dquote, t_token_list **list, int j)
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

t_err	dquote_dollar_token(const char *dquote, int *j, t_token_list **list)
{
	char	*key;

	(*j)++;
	if (dquote[*j] == '\0' || ft_isspace(dquote[*j]))
		return (add_literal_dollar(list));
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

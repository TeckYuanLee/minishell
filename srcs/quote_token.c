#include "minishell.h"

t_err	save_quote(const char *line, char **quote)
{
	int		i;

	i = 0;
	while (char_is_allowed(line[i], "'\0"))
		i++;
	if (line[i] != '\'')
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

t_err	save_dquote(const char *line, char **dquote)
{
	int		i;

	i = 0;
	while (char_is_allowed(line[i], "\"\0"))
		i++;
	if (line[i] != '"')
	{
		ft_putstr_fd("minishell: syntax error open-ended ", 2);
		ft_putstr_fd("quote (unsupported)\n", 2);
		return (SYNTAX_ERR);
	}
	*dquote = malloc(i + 1);
	if (!*dquote)
		return (MALLOC_FAIL);
	ft_strlcpy(*dquote, line, i + 1);
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
		{
			if (dquote_dollar_token(dquote, &j, list) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		}
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
	if (add_new_token_to_list(list, TOK_QUOTE, word) == MALLOC_FAIL)
	{
		free (word);
		return (MALLOC_FAIL);
	}
	return (NO_ERROR);
}

char	*save_word(const char *input)
{
	char	*word;
	int		i;

	i = 0;
	while (char_is_allowed(input[i], "<>|$';\"\\[]{}()") && \
			!isspace(input[i]))
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, input, i + 1);
	return (word);
}
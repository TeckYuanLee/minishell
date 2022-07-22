#include "minishell.h"

t_err	space_token(const char *line, int *i, t_token_list **list)
{
	t_token_list	*new_token;
	int				j;

	j = 0;
	while (isspace(line[j]))
		j++;
	new_token = create_token(TOK_SPACE, NULL);
	if (!new_token)
		return (MALLOC_FAIL);
	add_to_tokenlist(list, new_token);
	*i = *i + j;
	return (NO_ERROR);
}

t_err	word_token(const char *input, int *i, t_token_list **list)
{
	t_token_list	*new_token;
	char			*word;

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
	*i = *i + ft_strlen(new_token->data);
	return (NO_ERROR);
}

t_err	dquote_token(const char *line, int *i, t_token_list **list)
{
	t_token_list	*new_token;
	char			*dquote;
	t_err			err;

	err = save_dquote(line + 1, &dquote);
	if (err != NO_ERROR)
		return (err);
	*i = *i + ft_strlen(dquote) + 2;
	if (ft_strchr(dquote, '$'))
		return (expand_dquote(dquote, list));
	new_token = create_token(TOK_DQUOTE, dquote);
	if (!new_token)
	{
		free (dquote);
		return (MALLOC_FAIL);
	}
	add_to_tokenlist(list, new_token);
	return (NO_ERROR);
}

t_err	quote_token(const char *line, int *i, t_token_list **list)
{
	t_token_list	*new_token;
	char			*quote;
	t_err			err;

	err = save_quote(line + 1, &quote);
	if (err != NO_ERROR)
		return (err);
	new_token = create_token(TOK_QUOTE, quote);
	if (!new_token)
	{
		free (quote);
		return (MALLOC_FAIL);
	}
	add_to_tokenlist(list, new_token);
	*i = *i + ft_strlen(new_token->data) + 2;
	return (NO_ERROR);
}

t_err	dollar_token(const char *line, int *i, t_token_list **list)
{
	t_token_list	*new_token;

	*i = *i + 1;
	if (line[1] == '\0' || isspace(line[1]))
		return (add_literal_dollar(list));
	else
	{
		if (ft_isdigit(line[1]))
		{
			*i = *i + 1;
			return (NO_ERROR);
		}
		if (line[1] == '?')
		{
			*i = *i +1;
			return (exitcode_token(line, i, list));
		}
	}
	new_token = create_token(TOK_DOLLAR, NULL);
	if (!new_token)
		return (MALLOC_FAIL);
	add_to_tokenlist(list, new_token);
	return (NO_ERROR);
}

t_err	pipe_token(char *input, int *i, t_token_list **list)
{
	t_token_list	*new_token;

	if (input[1] == '|')
		return (syntax_err_lexer((char)DOUBLE_PIPE));
	new_token = create_token(TOK_PIPE, NULL);
	if (!new_token)
		return (MALLOC_FAIL);
	add_to_tokenlist(list, new_token);
	if (!*list)
		return (MALLOC_FAIL);
	*i = *i + 1;
	return (NO_ERROR);
}

t_err	redir_out_token(const char *input, int *i, t_token_list **list)
{
	t_token_list	*new_token;

    if (input[1] == '>')
	{
		new_token = create_token(TOK_APPEND, NULL);
		*i = *i + 2;
	}
	else
	{
		new_token = create_token(TOK_REDIR_OUT, NULL);
		*i = *i + 1;
	}
	if (!new_token)
		return (MALLOC_FAIL);
	add_to_tokenlist(list, new_token);
	if (!*list)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

t_err	redir_in_token(const char *input, int *i, t_token_list **list)
{
	t_token_list	*new_token;

	if (input[1] == '<')
	{
		new_token = create_token(TOK_HERE_DOC, NULL);
		*i = *i + 2;
	}
	else
	{
		new_token = create_token(TOK_REDIR_IN, NULL);
		*i = *i + 1;
	}
	if (!new_token)
		return (MALLOC_FAIL);
	add_to_tokenlist(list, new_token);
	if (!*list)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

t_err	tokenize(char *input, int *i, t_token_list **list)
{
	if (*input == '<')
		return (redir_in_token(input, i, list));
	else if (*input == '>')
		return (redir_out_token(input, i, list));
	else if (*input == '|')
		return (pipe_token(input, i, list));
	else if (*input == '$')
		return (dollar_token(input, i, list));
	else if (*input == '\'')
		return (quote_token(input, i, list));
	else if (*input == '"')
		return (dquote_token(input, i, list));
	else
		return (word_token(input, i, list));
}

t_err	lexer(char *line, t_curr_input *input, t_envi *info)
{
	t_token_list	**list;
	int				i;
	t_err			err;

	(void)info;
	i = 0;
	list = &input->lexer;
	while (line[i])
	{
		if (isspace(line[i]))
			space_token(&line[i], &i, list);
		else if (!char_is_allowed(line[i], "\\;~{}[()^%#&"))
			return (syntax_err_lexer(line[i]));
		else
		{
			err = tokenize(&line[i], &i, list);
			if (err != NO_ERROR)
				return (err);
		}
	}
	return (NO_ERROR);
}

t_err	syntax_err_lexer(char token)
{
	ft_putstr_fd("minishell: syntax error unexpected token '", 2);
	if (token == (char)DOUBLE_PIPE)
		ft_putstr_fd("||", 2);
	else
		ft_putchar_fd(token, 2);
	ft_putstr_fd("' (unsupported)\n", 2);
	return (SYNTAX_ERR);
}
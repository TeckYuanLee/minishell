#include "minishell.h"

t_err	spaces(char *input, int *i, t_token_list **list)
{
	t_token_list	*new_token;
	int				j;

	j = 0;
	while (ft_isspace(input[j]))
		j++;
	new_token = create_token(TOK_SPACE, NULL);
	if (!new_token)
		return (MALLOC_FAIL);
	add_to_tokenlist(list, new_token);
	*i = *i + j;
	return (NO_ERROR);
}

t_err	words(char *input, int *i, t_token_list **list)
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

t_err	quotes(char *input, int *i, t_token_list **list)
{
	t_token_list	*new_token;
	char			*quote;
	t_err			err;

	err = save_quote(input + 1, &quote, input);
	if (err != NO_ERROR)
		return (err);
	*i = *i + ft_strlen(quote) + 2;
	if (*input == '"')
	{
		if (ft_strchr(quote, '$'))
			return (expand_dquote(quote, list));
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

t_err	pipes_dollars(char *input, int *i, t_token_list **list)
{
	t_token_list	*new_token;

	(*i)++;
	if (*input == '|')
	{
		if (input[1] == '|')
			return (syntax_err_lexer((char)DOUBLE_PIPE));
		new_token = create_token(TOK_PIPE, NULL);
	}
	else if (*input == '$')
	{
		if (input[1] == '\0' || ft_isspace(input[1]))
			return (add_literal_dollar(list));
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

t_err	lnr_angles(char *input, int *i, t_token_list **list)
{
	t_token_list	*new_token;

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

t_err	tokenize(char *input, int *i, t_token_list **list)
{
	if (*input == '<' || *input == '>')
		return (lnr_angles(input, i, list));
	else if (*input == '|' || *input == '$')
		return (pipes_dollars(input, i, list));
	else if (*input == '\'' || *input == '"')
		return (quotes(input, i, list));
	else
		return (words(input, i, list));
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
		if (ft_isspace(line[i]))
			spaces(&line[i], &i, list);
		else if (!allowed_char(line[i], "\\;~{}[()^%#&"))
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

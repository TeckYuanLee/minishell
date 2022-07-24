#include "minishell.h"

t_err	add_literal_dollar(t_token_list **list)
{
	char			*str;
	t_token_list	*new_token;

	str = ft_strdup("$");
	if (!str)
		return (MALLOC_FAIL);
	new_token = create_token(TOK_WORD, str);
	if (!new_token)
	{
		free (str);
		return (MALLOC_FAIL);
	}
	add_to_tokenlist(list, new_token);
	return (NO_ERROR);
}

t_err	exitcode_token(const char *dquote, int *j, t_token_list **list)
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

t_err	add_new_token(t_token_list **head, t_token_type type, char *data)
{
	t_token_list	*new;

	new = create_token(type, data);
	if (!new)
		return (MALLOC_FAIL);
	add_to_tokenlist(head, new);
	return (NO_ERROR);
}

t_token_list	*create_token(t_token_type type, char *data)
{
	static int		id = 0;
	t_token_list	*new_token;

	new_token = ft_calloc(sizeof(t_token_list), 1);
	if (new_token)
	{
		new_token->type = type;
		new_token->data = data;
		new_token->id = id++;
	}
	return (new_token);
}

#include "minishell.h"

//	copy word literal for word token /////
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

//	check if the char is allowed /////
t_bool	allowed_char(int c, char *not_allowed)
{
	if (ft_strchr(not_allowed, c))
		return (FALSE);
	return (TRUE);
}

//	create cmd and store in 2d array if not parsed /////
char	**create_cmd_split(t_token *list, int word_count)
{
	int		i;
	char	**split;

	split = ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (list && list->type != TOK_PIPE)
	{
		if (list->type == TOK_WORD && !list->is_parsed)
		{
			split[i] = ft_strdup(list->data);
			if (!split[i])
			{
				ft_free_partial_split(&split, i);
				return (NULL);
			}
			i++;
		}
		list = list->next;
	}
	return (split);
}

//	copy data and store in 2d array || essentially just strdup for redir_pass /////
char	**make_split(t_token *list, int word_amount)
{
	char	**split;
	int		i;

	(void)list;
	split = ft_calloc(word_amount + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	while (++i < word_amount)
	{
		split[i] = ft_strdup(list->data);
		if (!split[i])
		{
			ft_free_partial_split(&split, i);
			return (NULL);
		}
		list = list->next;
	}
	return (split);
}

//	retrieve token type in string format /////
char	*get_token_str(t_token_t type)
{
	static char	*strings[12] = {
		"WORD",
		"PIPE",
		"QUOTE",
		"DQUOTE",
		"DOLLAR",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HERE_DOC",
		"SPACE",
		"EMPTY_WORD",
		"TOK_ERROR"
	};

	return (strings[type]);
}

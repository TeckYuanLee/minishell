#include "minishell.h"

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

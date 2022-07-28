#include "minishell.h"

//	copy data and store in 2d array if not parsed
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

//	copy data and store in 2d array
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

//	add root node for pipe / no pipe node
t_err	add_tree_node(t_nodetype type, t_tree **tree, char **data)
{	
	if (type == PIPE || type == NO_PIPE)
	{
		if (!data)
			add_root_node(type, tree);
		else
			printf(BHRED "PIPE/NO_PIPE node should not have data!!\n" BHWHT);
	}
	else
		add_leaf_node(type, data, *tree);
	return (NO_ERROR);
}

//	print syntax error
t_err	syntax_err(t_token_type type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (type == TOK_PIPE)
		ft_putstr_fd("'|'\n", 2);
	else if (type == TOK_REDIR_IN)
		ft_putstr_fd("'<'\n", 2);
	else if (type == TOK_REDIR_OUT)
		ft_putstr_fd("'>'\n", 2);
	else if (type == TOK_APPEND)
		ft_putstr_fd("'>>'\n", 2);
	else if (type == TOK_HERE_DOC)
		ft_putstr_fd("'<<'\n", 2);
	return (SYNTAX_ERR);
}

//	retrieve token type in string format
char	*get_token_str(t_token_type type)
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

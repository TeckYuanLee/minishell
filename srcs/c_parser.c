#include "minishell.h"

//	check for word tokens and turn them into cmd /////
t_err	cmd_pass(t_token *list, t_tree **root)
{
	t_token	*node;
	int		word_count;
	char	**split;

	node = list;
	word_count = 0;
	while (node)
	{
		if (node->type == TOK_WORD && !node->parsed)
			word_count++;
		node = node->next;
	}
	split = create_cmd_split(list, word_count);
	if (!split)
		return (MALLOC_FAIL);
	add_leaf_node(CMD, split, *root);
	return (NO_ERROR);
}

//	create node for redir signs /////
t_err	redir_pass(t_token *list, t_tree **root)
{
	char	**split;

	while (list && list->type != TOK_PIPE)
	{
		if (list->type == TOK_WORD)
		{
			list = list->next;
			continue ;
		}
		split = make_split(list->next, 1);
		if (!split)
			return (MALLOC_FAIL);
		else if (list->type == TOK_REDIR_IN)
			add_leaf_node(REDIR_IN, split, *root);
		else if (list->type == TOK_REDIR_OUT)
			add_leaf_node(REDIR_OUT, split, *root);
		else if (list->type == TOK_APPEND)
			add_leaf_node(REDIR_APP, split, *root);
		else if (list->type == TOK_HERE_DOC)
			add_leaf_node(HERE_DOC, split, *root);
		list = list->next;
		list->parsed = 1;
	}
	return (NO_ERROR);
}

//	create a root node: PIPE or NOPIPE /////
t_err	root_pass(t_token *list, t_tree **root)
{
	(void)list;
	(void)root;
	if (next_branch(list))
		add_root_node(PIPE, root);
	else
		add_root_node(NO_PIPE, root);
	return (NO_ERROR);
}

//	check if lnr angles is input correctly, break if there is pipe /////
t_err	redir_syntax_pass(t_token *list)
{
	while (list)
	{
		if (list->type == TOK_PIPE)
			break ;
		else if (list->type == TOK_REDIR_IN || list->type == TOK_REDIR_OUT ||
				list->type == TOK_APPEND || list->type == TOK_HERE_DOC)
		{
			if (!list->next || list->next->type != TOK_WORD)
				return (syntax_err(list->type));
			else
				list = list->next;
		}
		else if (list->type == TOK_WORD)
			(void)list;
		list = list->next;
	}
	return (NO_ERROR);
}

//	check if pipe not start/end and no double pipe /////
t_err	pipe_syntax_pass(t_token *list)
{
	while (list)
	{
		if (list->type == TOK_PIPE)
		{
			if (!list->prev || !list->next)
				return (syntax_err(TOK_PIPE));
			if (list->prev->type == TOK_PIPE ||
				list->next->type == TOK_PIPE)
				return (syntax_err(TOK_PIPE));
		}
		list = list->next;
	}
	return (NO_ERROR);
}

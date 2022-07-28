#include "minishell.h"

//	check next branch for pipe else return null list
t_token	*next_branch(t_token *list)
{
	if (!list)
		printf(BHRED "[next_branch] Empty t_token ?\n" BHWHT);
	while (list)
	{
		list = list->next;
		if (list && list->type == TOK_PIPE)
			return (list);
	}
	return (list);
}

//	check for word tokens
t_err	cmd_pass(t_token *list, t_tree **root)
{
	t_token	*node;
	int		word_count;
	char	**split;

	node = list;
	word_count = 0;
	while (node)
	{
		if (node->type == TOK_WORD && !node->is_parsed)
			word_count++;
		node = node->next;
	}
	split = create_cmd_split(list, word_count);
	if (!split)
		return (MALLOC_FAIL);
	add_tree_node(CMD, root, split);
	return (NO_ERROR);
}

//	create node for redir signs
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
			add_tree_node(REDIR_IN, root, split);
		else if (list->type == TOK_REDIR_OUT)
			add_tree_node(REDIR_OUT, root, split);
		else if (list->type == TOK_APPEND)
			add_tree_node(REDIR_APP, root, split);
		else if (list->type == TOK_HERE_DOC)
			add_tree_node(HERE_DOC, root, split);
		list = list->next;
		list->is_parsed = TRUE;
	}
	return (NO_ERROR);
}

//	check if a root node exists
t_err	root_pass(t_token *list, t_tree **root)
{
	(void)list;
	(void)root;
	if (next_branch(list))
		add_tree_node(PIPE, root, NULL);
	else
		add_tree_node(NO_PIPE, root, NULL);
	return (NO_ERROR);
}

//	check if lnr angles is input correctly
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
		else
			printf(BHRED "[redir_syntax_pass Wrong tok_type?: %s\n" \
				BHWHT, get_token_str(list->type));
		list = list->next;
	}
	return (NO_ERROR);
}

//	check if pipe is input correctly
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

//	check tokens if they are used correctly
t_err	parser(char *line, t_curr_input *input, t_envi *info)
{
	t_token	*list;
	t_tree	**root;

	(void)line;
	(void)info;
	list = input->lexer;
	root = &input->tree;
	if (!list)
		return (printf(BHRED "[parser] Empty t_token\n" BHWHT));
	if (pipe_syntax_pass(list) != NO_ERROR)
		return (SYNTAX_ERR);
	while (list)
	{	
		if (redir_syntax_pass(list) != NO_ERROR)
			return (SYNTAX_ERR);
		root_pass(list, root);
		redir_pass(list, root);
		cmd_pass(list, root);
		list = next_branch(list);
		if (list && list->type == TOK_PIPE)
			list = list->next;
	}
	return (NO_ERROR);
}

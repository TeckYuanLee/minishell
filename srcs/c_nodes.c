#include "minishell.h"

//	simply get next node
t_tree	*get_next_node(t_tree *tree)
{
	if (!tree)
	{
		printf(BHRED "Empty forrest?!?!?\n");
		return (NULL);
	}
	if (tree->leaf)
		tree = tree->leaf;
	else
	{
		if (tree->type == PIPE || tree->type == NO_PIPE)
			return (tree->next_root);
		while (tree->prev && tree->type != PIPE && tree->type != NO_PIPE)
			tree = tree->prev;
		return (tree->next_root);
	}
	return (tree);
}

//	check next branch for pipe else return null list /////
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

//	traverse right of pipe or no pipe, else traverse leftmost
//	to search for pipe or no pipe /////
t_tree	*last_root_node(t_tree *tree)
{
	if (tree->type == PIPE || tree->type == NO_PIPE)
	{
		while (tree->next_root)
			tree = tree->next_root;
		return (tree);
	}
	while (tree->leaf)
		tree = tree->leaf;
	return (last_root_node(tree));
}

//	create new branch id if token type is pipe, else leave id /////
t_tree	*create_tree_node(t_node type, char **data)
{
	static int	branch_id = 0;
	static int	leave_id = 0;
	t_tree		*new_tree;

	new_tree = ft_calloc(sizeof(t_tree), 1);
	if (!new_tree)
		return (NULL);
	new_tree->type = type;
	new_tree->data = data;
	if (type == NO_PIPE || type == PIPE)
	{
		new_tree->id = branch_id++;
		leave_id = 0;
		if (type == NO_PIPE)
			branch_id = 0;
	}
	else
		new_tree->id = leave_id++;
	return (new_tree);
}

//	create and insert new node at leftmost node /////
t_err	add_leaf_node(t_node type, char **data, t_tree *parent)
{
	t_tree	*new_node;

	if (!parent)
		return (printf(BHRED "[add_child_node] No parent tree!?!?!\n" BHWHT));
	new_node = create_tree_node(type, data);
	if (!new_node)
		return (MALLOC_FAIL);
	while (parent->next_root)
		parent = parent->next_root;
	if (parent->leaf == NULL)
		parent->leaf = new_node;
	else
	{
		while (parent->leaf)
			parent = parent->leaf;
		parent->leaf = new_node;
	}
	new_node->prev = parent;
	return (NO_ERROR);
}

//	create root node // put new node after root node /////
t_err	add_root_node(t_node type, t_tree **head_tree)
{
	t_tree	*node;
	t_tree	*new_node;

	node = *head_tree;
	new_node = create_tree_node(type, NULL);
	if (!new_node)
		return (MALLOC_FAIL);
	if (!*head_tree)
	{
		*head_tree = new_node;
		return (NO_ERROR);
	}
	node = last_root_node(node);
	new_node->prev = node;
	node->next_root = new_node;
	return (NO_ERROR);
}

#include "minishell.h"

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

//	add root node for pipe / no pipe node, else add leaf node /////
t_err	add_tree_node(t_node_t type, t_tree **tree, char **data)
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

//	look for next root node /////
t_tree	*next_root_node(t_tree *tree)
{
	if (tree->type == PIPE || tree->type == NO_PIPE)
		return (tree->right_node);
	while (tree->up_node && tree->type != PIPE && tree->type != NO_PIPE)
		tree = tree->up_node;
	return (tree->right_node);
}

//	traverse right of pipe or no pipe, else traverse leftmost
//	to search for pipe or no pipe /////
t_tree	*last_root_node(t_tree *tree)
{
	if (tree->type == PIPE || tree->type == NO_PIPE)
	{
		while (tree->right_node)
			tree = tree->right_node;
		return (tree);
	}
	while (tree->left_node)
		tree = tree->left_node;
	return (last_root_node(tree));
}

//	create new branch id if token type is pipe, else leave id /////
t_tree	*create_tree_node(t_node_t type, char **data)
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
t_err	add_leaf_node(t_node_t type, char **data, t_tree *parent)
{
	t_tree	*new_node;

	if (!parent)
		return (printf(BHRED "[add_child_node] No parent tree!?!?!\n" BHWHT));
	new_node = create_tree_node(type, data);
	if (!new_node)
		return (MALLOC_FAIL);
	while (parent->right_node)
		parent = parent->right_node;
	if (parent->left_node == NULL)
		parent->left_node = new_node;
	else
	{
		while (parent->left_node)
			parent = parent->left_node;
		parent->left_node = new_node;
	}
	new_node->up_node = parent;
	return (NO_ERROR);
}

//	create root node // put new node after root node /////
t_err	add_root_node(t_node_t type, t_tree **head_tree)
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
	new_node->up_node = node;
	node->right_node = new_node;
	return (NO_ERROR);
}
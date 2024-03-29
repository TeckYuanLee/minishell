/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:32:49 by telee             #+#    #+#             */
/*   Updated: 2022/08/19 12:05:53 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	simply get next node
t_tree	*get_next_node(t_tree *tree)
{
	if (!tree)
		return (NULL);
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
	while (list)
	{
		list = list->next;
		if (list && list->type == TOK_PIPE)
			return (list);
	}
	return (list);
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
void	add_root_node(t_node type, t_tree **head_tree)
{
	t_tree	*new_node;
	t_tree	*node;

	node = *head_tree;
	new_node = create_tree_node(type, NULL);
	if (!new_node)
		return ;
	if (*head_tree)
	{
		while (1)
		{
			if ((node)->type == PIPE || (node)->type == NO_PIPE)
			{
				while ((node)->next_root)
					(node) = (node)->next_root;
				break ;
			}
			while ((node)->leaf)
				(node) = (node)->leaf;
		}
		new_node->prev = (node);
		(node)->next_root = new_node;
	}
	else
		*head_tree = new_node;
}

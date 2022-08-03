#include "minishell.h"

//  free envi parent /////
void	free_envi_parent(t_env *envi)
{
	clean_tree(envi->loc_tree_ptr);
	free(envi->exec);
}

//  free envp /////
void	free_envp(t_item *ms_envp)
{
	int			i;

	if (!ms_envp)
	{
		printf(BHRED "[free_envp] ms_envp == NULL ?!??\n" BHWHT);
		return ;
	}
	i = 0;
	while (ms_envp[i].key)
	{
		ft_free_str(&ms_envp[i].key);
		ft_free_str(&ms_envp[i].value);
		i++;
	}
	free (ms_envp);
}

//  clean rows /////
static void	clean_leaves(t_tree *root_tree)
{
	t_tree	*next_leave;

	while (root_tree)
	{
		next_leave = root_tree->left_node;
		ft_free_split(&root_tree->data);
		free (root_tree);
		root_tree = next_leave;
	}
}

//  clean rows columns by columns /////
void	clean_tree(t_tree **head_tree)
{
	t_tree	*node;
	t_tree	*next_root;

	node = *head_tree;
	if (!node)
		return ;
	while (node)
	{
		next_root = node->right_node;
		clean_leaves(node);
		node = next_root;
	}
	*head_tree = NULL;
}

//  free data from lexer /////
void	clean_lexer(t_token **list)
{
	t_token	*node;
	t_token	*temp;

	node = *list;
	if (!node)
		return ;
	while (node)
	{
		temp = node;
		ft_free_str(&node->data);
		node = temp->next;
		free (temp);
	}
	*list = NULL;
}
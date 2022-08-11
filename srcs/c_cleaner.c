#include "minishell.h"

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

//  clean rows columns by columns and rows by rows /////
void	clean_tree(t_tree **head_tree)
{
	t_tree	*node;
	t_tree	*next_root;
	t_tree	*next_leave;

	node = *head_tree;
	if (!node)
		return ;
	while (node)
	{
		next_root = node->next_root;
		while (node)
		{
			next_leave = node->leaf;
			ft_free_split(&node->data);
			free (node);
			node = next_leave;
		}
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
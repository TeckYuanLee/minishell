#include "minishell.h"

//	heredoc exists in previous node
int	prev_heredoc_exists(t_tree *tree)
{
	if (!tree)
		return (0);
	tree = tree->up_node;
	while (tree && tree->type != HERE_DOC)
		tree = tree->left_node;
	if (!tree)
		return (0);
	return (1);
}

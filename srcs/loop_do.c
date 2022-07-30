#include "minishell.h"

//  free envi parent
void	free_envi_parent(t_envi *envi)
{
	clean_tree(envi->loc_tree_ptr);
	free(envi->exec);
}

//  initialize executor
t_executor	*ft_init_exec(void)
{	
	t_executor	*new;

	new = ft_calloc(sizeof(t_executor), 1);
	if (!new)
		return (NULL);
	new->index = 0;
	new->builtin_check = 0;
	return (new);
}

//  start building tree
void	ft_start_tree(t_envi *envi, t_tree **tree)
{
	int	i;

	envi->exec = ft_init_exec();
	envi->loc_tree_ptr = tree;
	if (!envi->exec)
		ft_error_exec(5, 0, envi);
	i = ft_handle_tree(envi, *tree, envi->exec);
	if (i == 34 || i == 33)
		envi->exitcode = 1;
	unlink(".here_doc");
	free_envi_parent(envi);
}

//  ignore signals
void	ignore_signals(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

//  clean rows
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

//  clean rows columns by columns
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

//  free data from lexer
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

//  print newline
void	new_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//  initialize signals
void	init_signals(void)
{
	struct sigaction	sig_c;
	struct sigaction	sig_slash;

	ft_bzero(&sig_c, sizeof(struct sigaction));
	ft_bzero(&sig_slash, sizeof(struct sigaction));
	sig_c.sa_handler = new_prompt;
	sig_slash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig_c, NULL);
	sigaction(SIGQUIT, &sig_slash, NULL);
}

//  keep programm running
int	do_loop(t_curr_input *curr_input, t_envi *envi)
{
	char	*input;
	t_err	rv;

	while (1)
	{
		init_signals();
		if (get_input(envi, &input) == MALLOC_FAIL)
			return (-1);
		if (!input)
			continue ;
		rv = process_input(input, curr_input, envi);
		free (input);
		if (rv != NO_ERROR)
		{
			clean_tree(&curr_input->tree);
			clean_lexer(&curr_input->lexer);
			if (rv == MALLOC_FAIL)
				exit (-1);
			continue ;
		}
		ignore_signals();
		ft_start_tree(envi, &curr_input->tree);
	}
}

#include "minishell.h"

//  initialize executor /////
t_exec	*ft_init_exec(void)
{	
	t_exec	*new;

	new = ft_calloc(sizeof(t_exec), 1);
	if (!new)
		return (NULL);
	new->index = 0;
	new->builtin_check = 0;
	return (new);
}

//  start building tree /////
void	ft_start_tree(t_env *envi, t_tree **tree)
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
	clean_tree(envi->loc_tree_ptr);
	free(envi->exec);
}

//  change termios settings /////
void	set_term_settings(void)
{
	struct termios	termios_p;

	ft_bzero(&termios_p, sizeof(struct termios));
	tcgetattr(2, &termios_p);
	termios_p.c_lflag &= (~ECHOCTL | ISIG);
	tcsetattr(2, TCSANOW, &termios_p);
}

//  keep programm running /////
int	do_loop(t_input *input, t_env *envi)
{
	char	*curr_input;
	t_err	err;

	while (1)
	{
		init_signals();
		if (get_input(envi, &curr_input) == MALLOC_FAIL)
			return (-1);
		if (!curr_input)
			continue ;
		err = process_input(curr_input, input, envi);
		free (curr_input);
		if (err != NO_ERROR)
		{
			clean_tree(&input->tree);
			clean_lexer(&input->lexer);
			if (err == MALLOC_FAIL)
				exit (-1);
			continue ;
		}
		ignore_signals();
		ft_start_tree(envi, &input->tree);
	}
}

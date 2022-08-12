#include "minishell.h"

//  start building tree
void	ft_start_tree(t_env *ms_env, t_tree **tree)
{
	int	i;

	ms_env->exec = ft_calloc(sizeof(t_exec), 1);
	if (!ms_env->exec)
		ft_error_exec(5, 0, ms_env);
	ms_env->exec->index = 0;
	ms_env->exec->builtin_check = 0;
	i = ft_handle_tree(ms_env, *tree, ms_env->exec);
	if (i == 34 || i == 33)
		ms_env->exitcode = 1;
	unlink(".heredoc");
	free(ms_env->exec);
}

//  change termios settings
void	set_term_settings(void)
{
	struct termios	termios_p;

	ft_bzero(&termios_p, sizeof(struct termios));
	tcgetattr(2, &termios_p);
	termios_p.c_lflag &= (~ECHOCTL | ISIG);
	tcsetattr(2, TCSANOW, &termios_p);
}

//  keep programm running
int	do_loop(t_input *input, t_env *ms_env)
{
	char	*curr_input;
	t_err	err;

	while (1)
	{
		ms_signals("init");
		if (get_input(ms_env, &curr_input) == MALLOC_FAIL)
			return (-1);
		if (!curr_input)
			continue ;
		err = process_input(curr_input, input, ms_env);
		free (curr_input);
		if (err != NO_ERROR)
		{
			clean_tree(&input->tree);
			clean_lexer(&input->lexer);
			if (err == MALLOC_FAIL)
				exit (-1);
			continue ;
		}
		ms_signals("ignore");
		ft_start_tree(ms_env, &input->tree);
	}
}

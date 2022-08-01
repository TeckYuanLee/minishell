#include "minishell.h"

//  free envp
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

//  exit signal /////
int	ft_exit_sig(t_env *envi)
{
	tcsetattr(2, TCSANOW, &envi->termios_p);
	rl_replace_line("exit", 0);
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 1);
	ft_free_split(&envi->var);
	free_envp(envi->ms_envp);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(0);
}

//  restore terminal settings
// void	restore_term_settings(struct termios *termios_p)
// {
// 	tcsetattr(2, TCSANOW, termios_p);
// }

//  change termios settings /////
void	set_term_settings(void)
{
	struct termios	termios_p;

	ft_bzero(&termios_p, sizeof(struct termios));
	tcgetattr(2, &termios_p);
	termios_p.c_lflag &= (~ECHOCTL | ISIG);
	tcsetattr(2, TCSANOW, &termios_p);
}

//	process input into lexer, expander, parser /////
t_err	process_input(char *line, t_input *input, t_env *info)
{
	t_err	err;

	err = lexer(line, input);
	if (err == NO_ERROR)
		err = expander(line, input, info);
	if (err == NO_ERROR)
		err = parser(line, input, info);
	if (err != NO_ERROR)
	{
		if (err == SYNTAX_ERR)
			info->exitcode = 258;
		return (err);
	}
	clean_lexer(&input->lexer);
	return (NO_ERROR);
}

//  get input from readline after removing whitespace /////
t_err	get_input(t_env *envi, char **input_ptr)
{
	char	*temp;

	set_term_settings();
	rl_replace_line("", 0);
	*input_ptr = readline(BHYEL PROMPT BHWHT);
	tcsetattr(2, TCSANOW, &envi->termios_p);
	if (*input_ptr && (*input_ptr)[0])
	{
		temp = *input_ptr;
		*input_ptr = ft_strtrim_white(temp);
		free(temp);
		if (!*input_ptr)
			return (MALLOC_FAIL);
		add_history(*input_ptr);
	}
	else if (!*input_ptr)
		ft_exit_sig(envi);
	return (NO_ERROR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_loop_do.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:30:01 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:30:01 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  start building tree
void	start_tree(t_env *ms_env, t_tree **tree)
{
	int	i;

	ms_env->exec = ft_calloc(sizeof(t_exec), 1);
	if (!ms_env->exec)
		exec_error(5, 0, ms_env);
	ms_env->exec->index = 0;
	ms_env->exec->builtin_check = 0;
	ms_env->tree_addr = tree;
	i = build_tree(ms_env, *tree, ms_env->exec);
	if (i == 34 || i == 33)
		ms_env->exitcode = 1;
	unlink(".heredoc");
	clean_tree(ms_env->tree_addr);
	free(ms_env->exec);
}

//	do lexer
t_err	lexer(char *line, t_input *input)
{
	t_token	**list;
	int		i;
	t_err	err;

	i = 0;
	input->lexer = NULL;
	list = &input->lexer;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			spaces(&line[i], &i, list);
		else if (!allowed_char(line[i], "\\;~{}[()^%#&"))
			return (syntax_err_lexer(line[i]));
		else
		{
			err = tokenize(&line[i], &i, list);
			if (err != NO_ERROR)
				return (err);
		}
	}
	return (NO_ERROR);
}

//	process input into lexer, expander, parser
t_err	process_input(char *line, t_input *input, t_env *info)
{
	t_err	err;

	err = lexer(line, input);
	if (err == NO_ERROR)
		err = expander(input, info);
	if (err == NO_ERROR)
		err = parser(input);
	if (err != NO_ERROR)
	{
		if (err == SYNTAX_ERR)
			info->exitcode = 258;
		return (err);
	}
	clean_lexer(&input->lexer);
	return (NO_ERROR);
}

//  get input from readline after removing whitespace
t_err	get_input(t_env *ms_env, char **input_ptr)
{
	char	*temp;

	set_term_settings();
	rl_replace_line("", 0);
	*input_ptr = readline(BHYEL PROMPT BHWHT);
	tcsetattr(2, TCSANOW, &ms_env->termios_p);
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
		exit_signal(ms_env);
	return (NO_ERROR);
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
		start_tree(ms_env, &input->tree);
	}
}

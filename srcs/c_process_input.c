#include "minishell.h"

//	check tokens if they are used correctly /////
t_err	parser(t_input *input)
{
	t_token	*list;
	t_tree	**root;

	list = input->lexer;
	root = &input->tree;
	if (!list)
		return (printf(BHRED "[parser] Empty t_token\n" BHWHT));
	if (pipe_syntax_pass(list) != NO_ERROR)
		return (SYNTAX_ERR);
	while (list)
	{	
		if (redir_syntax_pass(list) != NO_ERROR)
			return (SYNTAX_ERR);
		root_pass(list, root);
		redir_pass(list, root);
		cmd_pass(list, root);
		list = next_branch(list);
		if (list && list->type == TOK_PIPE)
			list = list->next;
	}
	return (NO_ERROR);
}

//	expand tokens /////
t_err	expander(t_input *input, t_env *info)
{
	t_err	err;
	t_token	**list;

	list = &input->lexer;
	if (!*list)
		return (EMPTY);
	err = rm_double_tokens(list, TOK_DOLLAR);
	if (err == NO_ERROR)
		err = quotes_to_words(list);
	if (err == NO_ERROR)
		err = expand_dollars(list, info);
	if (err == NO_ERROR)
		err = word_join(list);
	if (err == NO_ERROR)
		return (rm_token_type(list, TOK_SPACE));
	return (err);
}

//	do lexer /////
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

//	process input into lexer, expander, parser /////
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

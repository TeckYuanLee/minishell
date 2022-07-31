/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:25:12 by telee             #+#    #+#             */
/*   Updated: 2022/07/25 14:14:06 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	tokenize symbols
t_err	tokenize(char *input, int *i, t_token **list)
{
	if (*input == '<' || *input == '>')
		return (lnr_angles(input, i, list));
	else if (*input == '|' || *input == '$')
		return (pipes_dollars(input, i, list));
	else if (*input == '\'' || *input == '"')
		return (quotes(input, i, list));
	else
		return (words(input, i, list));
}

t_err	syntax_err_lexer(char token)
{
	ft_putstr_fd("minishell: syntax error unexpected token '", 2);
	if (token == (char)DOUBLE_PIPE)
		ft_putstr_fd("||", 2);
	else
		ft_putchar_fd(token, 2);
	ft_putstr_fd("' (unsupported)\n", 2);
	return (SYNTAX_ERR);
}

//	do lexer
t_err	lexer(char *line, t_input *input, t_env *info)
{
	t_token	**list;
	int		i;
	t_err	err;

	(void)info;
	i = 0;
	list = NULL;
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

	err = lexer(line, input, info);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:25:12 by telee             #+#    #+#             */
/*   Updated: 2022/08/01 15:38:02 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	tokenize symbols /////
t_err	tokenize(char *input, int *i, t_token **list)
{
	if (*input == '<' || *input == '>')
		return (lnr_angles(input, i, list));
	else if (*input == '|')
		return (pipes(input, i, list));
	else if (*input == '$')
		return (dollars(input, i, list));
	else if (*input == '\'' || *input == '"')
		return (quotes(input, i, list));
	else
		return (words(input, i, list));
}

//	disallowed char from lexer /////
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

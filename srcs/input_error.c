/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:28:41 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:28:43 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//	print syntax error /////
t_err	syntax_err(t_token_t type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (type == TOK_PIPE)
		ft_putstr_fd("'|'\n", 2);
	else if (type == TOK_REDIR_IN)
		ft_putstr_fd("'<'\n", 2);
	else if (type == TOK_REDIR_OUT)
		ft_putstr_fd("'>'\n", 2);
	else if (type == TOK_APPEND)
		ft_putstr_fd("'>>'\n", 2);
	else if (type == TOK_HERE_DOC)
		ft_putstr_fd("'<<'\n", 2);
	return (SYNTAX_ERR);
}

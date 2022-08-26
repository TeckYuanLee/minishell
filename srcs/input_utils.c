/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:30:24 by telee             #+#    #+#             */
/*   Updated: 2022/08/26 09:41:03 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	disallowed char from lexer /////
t_err	syntax_err_lexer(char token)
{
	ft_putstr_fd("minishell: unexpected token '", 2);
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

//	check if the char is allowed /////
int	allowed_char(int c, char *not_allowed)
{
	if (ft_strchr(not_allowed, c))
		return (0);
	return (1);
}

//	create cmd and store in 2d array if not parsed /////
char	**create_cmd_split(t_token *list, int word_count)
{
	int		i;
	char	**split;

	split = ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (list && list->type != TOK_PIPE)
	{
		if (list->type == TOK_WORD && !list->parsed)
		{
			split[i] = ft_strdup(list->data);
			if (!split[i])
			{
				free_split(&split);
				return (NULL);
			}
			i++;
		}
		list = list->next;
	}
	return (split);
}

//	copy data and store in 2d array || 
//	essentially just strdup for redir_pass
char	**make_split(t_token *list, int word_amount)
{
	char	**split;
	int		i;

	(void)list;
	split = ft_calloc(word_amount + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	while (++i < word_amount)
	{
		split[i] = ft_strdup(list->data);
		if (!split[i])
		{
			free_split(&split);
			return (NULL);
		}
		list = list->next;
	}
	return (split);
}

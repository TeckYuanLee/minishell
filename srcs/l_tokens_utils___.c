/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:25:15 by telee             #+#    #+#             */
/*   Updated: 2022/07/25 09:25:15 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	check if the char is allowed /////
t_bool	allowed_char(int c, char *not_allowed)
{
	if (ft_strchr(not_allowed, c))
		return (FALSE);
	return (TRUE);
}

//	add created token to the tokenlist /////
void	add_to_tokenlist(t_token **head, t_token *new)
{
	t_token	*node;

	node = NULL;
	if (!*head)
		*head = new;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		new->prev = node;
		node->next = new;
	}
}

//	handle '$?' /////
t_err	exitcode_token(const char *dquote, int *j, t_token **list)
{
	char	*question;

	(void)dquote;
	(void)j;
	question = ft_strdup("?");
	if (!question)
		return (MALLOC_FAIL);
	if (add_new_token(list, TOK_DOLLAR, NULL) == MALLOC_FAIL)
	{
		free(question);
		return (MALLOC_FAIL);
	}
	if (add_new_token(list, TOK_WORD, question) == MALLOC_FAIL)
	{
		free(question);
		return (MALLOC_FAIL);
	}
	return (NO_ERROR);
}

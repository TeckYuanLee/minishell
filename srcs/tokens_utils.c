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

t_err	get_env_key(const char *str, char **return_key)
{
	int		i;

	*return_key = NULL;
	i = 0;
	if (ft_isdigit(*str))
		return (KEY_ERR);
	while (allowed_char(str[i], "$()<>'/\\;=.\0") && !ft_isspace(str[i]))
		i++;
	*return_key = ft_calloc(i + 1, 1);
	if (!*return_key)
		return (MALLOC_FAIL);
	ft_strlcpy(*return_key, str, i + 1);
	return (NO_ERROR);
}

t_bool	allowed_char(int c, char *not_allowed)
{
	if (ft_strchr(not_allowed, c))
		return (FALSE);
	return (TRUE);
}

void	add_to_tokenlist(t_token **head, t_token *new)
{
	t_token	*node;

	node = NULL;
	if (!*head)
		*head = new;
	else
	{
		node = *head;
		// printf("yes\n");
		// printf("current:%s\n", node->data);
		// printf("next:%s\n", node->next->data);
		while (node->next)
		{
			// printf("moved\n");
			// printf("%s\n", node->data);
			node = node->next;
		}
		new->prev = node;
		node->next = new;
	}
}

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

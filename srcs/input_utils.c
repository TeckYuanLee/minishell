/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:30:24 by telee             #+#    #+#             */
/*   Updated: 2022/08/19 10:38:18 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

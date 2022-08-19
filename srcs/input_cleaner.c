/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:06:38 by telee             #+#    #+#             */
/*   Updated: 2022/08/19 19:44:08 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	free 2D array
void	free_split(char ***split)
{
	int	i;

	i = -1;
	if (!*split)
		return ;
	while ((*split)[++i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
	}
	free(*split);
	*split = NULL;
}

//  free ms_env
void	free_ms_env(t_item *item)
{
	int			i;

	if (!item)
		return ;
	i = -1;
	while (item[++i].key)
	{
		free(item[i].key);
		free(item[i].value);
	}
	free (item);
}

//	free env variables
void	free_envi(t_env *ms_env, int exitcode)
{
	clean_tree(ms_env->tree_addr);
	free(ms_env->exec);
	free_split(&ms_env->envp);
	free_ms_env(ms_env->item);
	close(0);
	close(1);
	if (exitcode != -100)
		exit(exitcode);
}

//  clean rows columns by columns and rows by rows
void	clean_tree(t_tree **head_tree)
{
	t_tree	*node;
	t_tree	*next_root;
	t_tree	*next_leave;

	node = *head_tree;
	if (!node)
		return ;
	while (node)
	{
		next_root = node->next_root;
		while (node)
		{
			next_leave = node->leaf;
			free_split(&node->data);
			free (node);
			node = next_leave;
		}
		node = next_root;
	}
	*head_tree = NULL;
}

//  free data from lexer
void	clean_lexer(t_token **list)
{
	t_token	*node;
	t_token	*temp;

	node = *list;
	if (!node)
		return ;
	while (node)
	{
		temp = node;
		free(node->data);
		node = temp->next;
		free (temp);
	}
	*list = NULL;
}

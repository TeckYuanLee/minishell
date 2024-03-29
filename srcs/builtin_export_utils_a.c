/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_a.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:27:25 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:27:25 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_len(t_item *item)
{
	int	i;

	i = 0;
	while (item->key)
	{
		item++;
		i++;
	}
	return (i);
}

//	if keys are match, fill array
void	mark_array(char *key, t_item *item, int *arr)
{
	int	i;

	i = 0;
	while (item->key)
	{
		if (ft_strncmp(key, item->key, ft_strlen(key) + 1) == 0)
		{
			*(arr + i) = 1;
			return ;
		}
		item++;
		i++;
	}
}

//	
void	print_key(char *key, t_item *item)
{
	while (item->key)
	{
		if (ft_strncmp(key, item->key, ft_strlen(key) + 1) == 0)
		{
			if (item->value)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(item->key, 1);
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(item->value, 1);
				ft_putstr_fd("\"\n", 1);
			}
			else
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(item->key, 1);
				ft_putstr_fd("\n", 1);
			}
		}
		item++;
	}
}

//	check for the smallest key
int	smallest_ms_env(char *key, t_item *item, int *arr)
{
	if (*(arr) == 1)
		return (0);
	if (ft_strncmp(item->key, key, ft_strlen(item->key) + 1) < 0)
		return (1);
	return (0);
}

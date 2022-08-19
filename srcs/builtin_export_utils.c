/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:27:28 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:27:28 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	look for first available key
char	*first_ms_env(t_item *item, int *arr, int arr_len)
{
	int	i;

	i = -1;
	while (++i < arr_len)
		if (*(arr + i) == 0)
			return ((item + i)->key);
	return (0);
}

//	print first available envp and mark array
t_err	print_first_ms_env(t_item *item, int *arr, int arr_len)
{
	int			i;
	static char	*smallest_key = NULL;
	static char	full_key[255];

	i = 0;
	ft_memchr(full_key, '~', 256);
	if (smallest_key == NULL)
		smallest_key = full_key;
	else
		smallest_key = first_ms_env(item, arr, arr_len);
	while (i < arr_len)
	{
		if (smallest_ms_env(smallest_key, item + i, arr + i))
		{
			smallest_key = (item + i)->key;
			i = 0;
			continue ;
		}
		i++;
	}
	print_key(smallest_key, item);
	mark_array(smallest_key, item, arr);
	return (NO_ERROR);
}

//	check for next position in array
int	export_not_ready(int *arr, int arr_len)
{
	int	i;

	i = -1;
	while (++i < arr_len)
		if (*(arr + i) == 0)
			return (1);
	return (0);
}

//	if key doesn't exist, add to envp, else update value
t_err	add_to_ms_env(t_item **item, char *key, char *value)
{
	if (!ms_env_key(key, *item))
	{
		if (update_ms_env(key, value, item) == MALLOC_FAIL)
		{
			free(key);
			return (MALLOC_FAIL);
		}
		return (NO_ERROR);
	}
	update_value(key, value, *item);
	free (key);
	return (NO_ERROR);
}

//	join old value with value
t_err	join_values(char *value, char *key, t_item *item, char **joined)
{
	char	*old_value;
	char	*temp;

	temp = NULL;
	if (get_env_value(item, key, &old_value) == MALLOC_FAIL)
	{
		free(key);
		free(value);
		return (MALLOC_FAIL);
	}
	if (old_value && value)
	{
		temp = ft_strjoin(old_value, value);
		free(old_value);
		free(value);
		if (!temp)
			return (MALLOC_FAIL);
	}
	else if (!old_value)
		temp = value;
	*joined = temp;
	return (NO_ERROR);
}

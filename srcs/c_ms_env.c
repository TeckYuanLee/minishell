/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ms_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:41:32 by telee             #+#    #+#             */
/*   Updated: 2022/08/12 16:48:34 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  check if key ms_env exists
int	ms_env_key(char *key, t_item *item)
{
	int	key_len;

	key_len = ft_strlen(key);
	while (item->key)
	{
		if (ft_strncmp(item->key, key, key_len + 1) == 0)
			return (1);
		item++;
	}
	return (0);
}

//  update ms_env with latest value
t_err	update_value(char *key, char *value, t_item *envp)
{
	int	i;

	i = -1;
	while (envp[++i].key)
	{
		if (ft_strncmp(envp[i].key, key, ft_strlen(key) + 1) == 0)
		{
			if (envp[i].value)
				free(envp[i].value);
			envp[i].value = value;
			break ;
		}
	}
	return (NO_ERROR);
}

//  add keys and values into ms_env
t_err	update_ms_env(char *key, char *value, t_item **head)
{
	t_item	*new_envp;
	int		i;

	i = 0;
	while ((head[i])->key)
		i++;
	new_envp = ft_calloc(i + 2, sizeof(t_item));
	if (!new_envp)
		return (MALLOC_FAIL);
	i = -1;
	while (head[++i]->key)
	{
		new_envp[i].key = head[i]->key;
		new_envp[i].value = head[i]->value;
	}
	new_envp[i].key = key;
	new_envp[i].value = value;
	free(*head);
	*head = new_envp;
	return (NO_ERROR);
}

/*
1. loop through keys
2. if key matches, extract value
3. else value is NULL
*/
t_err	get_env_value(t_item *item, char *key, char **value_ptr)
{
	int	i;

	i = -1;
	while (item[++i].key)
	{
		if (!(ft_strncmp(item[i].key, key, ft_strlen(key) + 1)))
		{
			if (item[i].value)
			{
				*value_ptr = ft_strdup(item[i].value);
				if (!*value_ptr)
					return (MALLOC_FAIL);
				return (NO_ERROR);
			}
			else
			{
				*value_ptr = NULL;
				return (NO_VALUE);
			}
		}
	}
	*value_ptr = NULL;
	return (NO_KEY);
}

/*
1. make sure first char not digit
2. while no disallowed char and no spaces, i++
3. malloc and strlcpy key from envp
*/
t_err	get_env_key(const char *str, char **return_key)
{
	int	i;

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

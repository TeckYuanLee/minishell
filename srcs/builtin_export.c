/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:27:30 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:27:30 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	extract value and add to list of envp
t_err	extract_to_ms_env(char *str, t_item **item, char *key)
{
	char	*value;

	value = NULL;
	if (str[ft_strlen(key)] == '=' || str[ft_strlen(key)] == '+')
	{
		str = ft_strchr(str, '=');
		if (str)
			str++;
		value = ft_strdup(str);
		if (!value)
		{
			free(key);
			return (MALLOC_FAIL);
		}
	}
	if (str[ft_strlen(key)] == '+')
		if (join_values(value, key, *item, &value) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	if (str[ft_strlen(key)] == '=' || str[ft_strlen(key)] == '\0')
		return (add_to_ms_env(item, key, value));
	return (NO_ERROR);
}

//	identify if it is an export key
int	export_key(char *key)
{
	size_t	i;

	i = 0;
	if (!key || !*key)
		return (0);
	if (ft_isdigit(key[0]) || key[0] == '-')
		return (0);
	while (key[i] && allowed_char(key[i], "'=\"-#+^~.|&@!;()<>*\\"))
		i++;
	if (ft_strlen(key) == i)
		return (1);
	return (0);
}

//	copy str to return key
t_err	dup_env_key(const char *str, char **return_key)
{
	int		i;

	*return_key = NULL;
	i = 0;
	if (ft_isdigit(*str))
		return (KEY_ERR);
	while (allowed_char(str[i], "=+\0") && !ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '=')
		return (KEY_ERR);
	*return_key = ft_calloc(i + 1, 1);
	if (!*return_key)
		return (MALLOC_FAIL);
	ft_strlcpy(*return_key, str, i + 1);
	return (NO_ERROR);
}

//	check if export is ready
t_err	ready_export(t_item *item)
{
	int	arr_len;
	int	*arr;

	// arr_len = 0;
	// while (item->key)
	// {
	// 	item++;
	// 	arr_len++;
	// }
	arr_len = get_ms_envp_len(item);
	arr = ft_calloc(arr_len, sizeof(int));
	if (!arr)
		return (MALLOC_FAIL);
	while (not_ready(arr, arr_len))
	{
		if (print_smallest_and_mark_arr(item, arr, arr_len) == MALLOC_FAIL)
		{
			free(arr);
			return (MALLOC_FAIL);
		}
	}
	free(arr);
	return (0);
}

//	handle export command
int	ms_export(char **argv, t_env *ms_env)
{
	int		i;
	char	*key;
	int		exitcode;

	if (!argv[1])
		return (ready_export(ms_env->item));
	exitcode = 0;
	i = 1;
	while (argv[i])
	{
		if (dup_env_key(argv[i], &key) == MALLOC_FAIL)
			return (-1);
		if (!export_key(key))
		{
			free(key);
			exitcode = export_error_msg(argv[i]);
		}
		else
			extract_to_ms_env(argv[i], &ms_env->item, key);
		i++;
	}
	if (ms_env_to_envp(ms_env->item, &ms_env->envp) == MALLOC_FAIL)
		return (-1);
	return (exitcode);
}

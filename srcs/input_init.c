/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:29:18 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:29:18 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  join env key and value
t_err	key_and_value(t_item *item, char **envp)
{
	char	*temp;
	char	*joined;

	if (item->value)
	{
		temp = ft_strjoin(item->key, "=");
		if (!temp)
			return (MALLOC_FAIL);
		joined = ft_strjoin(temp, item->value);
		free (temp);
	}
	else
		joined = ft_strdup(item->key);
	if (!joined)
		return (MALLOC_FAIL);
	*envp = joined;
	return (NO_ERROR);
}

// form envp by combining key and value
t_err	ms_env_to_envp(t_item *item, char ***envp)
{
	int	i;
	int	j;

	i = 0;
	while (item[i].key)
		i++;
	if (*envp)
		free_split(envp);
	*envp = ft_calloc(i + 1, sizeof(char *));
	if (!*envp)
		return (MALLOC_FAIL);
	j = -1;
	while (++j < i)
	{
		if (key_and_value(&item[j], &(*envp)[j]) == MALLOC_FAIL)
		{
			free_split(envp);
			return (MALLOC_FAIL);
		}
	}
	return (NO_ERROR);
}

//  update shell lvl
t_err	update_shlvl(t_env *ms_env)
{
	int		shlvl;
	char	*value;

	if (get_env_value(ms_env->item, "SHLVL", &value) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (!value)
		shlvl = 0;
	else
		shlvl = ft_atoi(value);
	if (value)
		free(value);
	value = ft_itoa(++shlvl);
	if (!value)
		return (MALLOC_FAIL);
	if (ms_env_key("SHLVL", ms_env->item))
		return (update_value("SHLVL", value, ms_env->item));
	return (update_ms_env("SHLVL", value, &ms_env->item));
}

/*
1. get key from envp_str
2. get value from envp_str
*/
t_err	envp_to_ms_env(char *envp_str, t_item *item)
{
	if (get_env_key(envp_str, &item->key) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ft_strlen(item->key) < ft_strlen(envp_str))
	{
		item->value = ft_strdup(envp_str + ft_strlen(item->key) + 1);
		if (!item->value)
		{
			free (item->key);
			return (MALLOC_FAIL);
		}
	}
	else
		item->value = NULL;
	return (NO_ERROR);
}

/*
1. bzero ms_env
2. copy from envp to ms_env
3. create key "OLDPWD"
*/
// should be able to replace ms_env_key with update_ms_env in cd
t_err	init_ms_env(char **envp, t_env *ms_env)
{
	int	i;

	i = 0;
	ft_bzero(ms_env, sizeof(t_env));
	while (envp[i])
		i++;
	ms_env->item = ft_calloc(i + 2, sizeof(t_item));
	if (!ms_env->item)
		return (MALLOC_FAIL);
	i = -1;
	while (envp[++i])
		envp_to_ms_env(envp[i], &ms_env->item[i]);
	if (!ms_env_key("OLDPWD", ms_env->item))
		ms_env->item->key = ft_strdup("OLDPWD");
	if (!ms_env->item->key)
		return (MALLOC_FAIL);
	if (update_shlvl(ms_env) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

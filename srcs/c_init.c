#include "minishell.h"

//  add keys and values into envp /////
t_err	add_to_ms_envp(char *key, char *value, t_item **head)
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

//  update shell lvl
t_err	update_shlvl(t_env *envi)
{
	int		lvl;
	char	*value;

	if (get_env_value(envi->item, "SHLVL", &value) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (!value)
		lvl = 0;
	else
		lvl = ft_atoi(value);
	if (lvl)
		free(value);
	value = ft_itoa(++lvl);
	if (!value)
		return (MALLOC_FAIL);
	if (ms_env_key("SHLVL", envi->item))
		return (update_value("SHLVL", value, envi->item));
	return (add_to_ms_envp("SHLVL", value, &envi->item));
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
		ft_free_split(envp);
	*envp = ft_calloc(i + 1, sizeof(char *));
	if (!*envp)
		return (MALLOC_FAIL);
	j = -1;
	while (++j < i)
	{
		if (key_and_value(&item[j], &(*envp)[j]) == MALLOC_FAIL)
		{
			ft_free_partial_split(envp, j);
			return (MALLOC_FAIL);
		}
	}
	return (NO_ERROR);
}

/*
1. bzero ms_env
2. copy from envp to ms_env
3. create key "OLDPWD"
*/
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
	{
		ms_env->item->key = ft_strdup("OLDPWD");
		if (!ms_env->item->key)
			return (MALLOC_FAIL);
	}
	return (NO_ERROR);
}

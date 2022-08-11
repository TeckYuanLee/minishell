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

//  copy from env key and value to envp ///// ok
t_err	envp_to_ms_envp(char *envp_str, t_item *ms_envp)
{
	char	*key;
	char	*value;

	if (!envp_str)
		return (printf(BHRED "[copy_to_custom_envp] envp_str to NULL..\n" BHWHT));
	if (get_env_key(envp_str, &key) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ft_strlen(key) < ft_strlen(envp_str))
	{
		if (envp_str[ft_strlen(key)] != '=')
			return (printf(BHRED "[copy_to_custom_envp] no '=' sign..\n" BHWHT));
		value = ft_strdup(envp_str + ft_strlen(key) + 1);
		if (!value)
		{
			free (key);
			return (MALLOC_FAIL);
		}
	}
	else
		value = NULL;
	ms_envp->key = key;
	ms_envp->value = value;
	return (NO_ERROR);
}

//  update shell lvl /////
t_err	update_shlvl(t_env *envi)
{
	int		lvl;
	char	*value;

	if (get_env_value(envi->ms_envp, "SHLVL", &value) == MALLOC_FAIL)
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
	if (ms_envp_key("SHLVL", envi->ms_envp))
		return (update_value("SHLVL", value, envi->ms_envp));
	return (add_to_ms_envp("SHLVL", value, &envi->ms_envp));
}

//  combine key values from envp with variables /////
t_err	ms_envp_to_var(t_item *ms_envp, char ***env_var)
{
	int	i;
	int	j;

	if (!ms_envp)
		return (printf(BHRED "[ms_envp_to_env_var] ms_envp = NULL\n" BHWHT));
	i = 0;
	while (ms_envp[i].key)
		i++;
	if (*env_var)
		ft_free_split(env_var);
	*env_var = ft_calloc(i + 1, sizeof(char *));
	if (!*env_var)
		return (MALLOC_FAIL);
	j = -1;
	while (++j < i)
	{
		if (combine_key_value(&ms_envp[j], &(*env_var)[j]) == MALLOC_FAIL)
		{
			ft_free_partial_split(env_var, j);
			return (MALLOC_FAIL);
		}
	}
	return (NO_ERROR);
}

//  initialize variables in envi ///// ok
t_err	init_ms_env(char **envp, t_env *ms_env)
{
	int	i;

	i = 0;
	ft_bzero(ms_env, sizeof(t_env));
	while (envp[i])
		i++;
	ms_env->ms_envp = ft_calloc(i + 2, sizeof(t_item));
	if (!ms_env->ms_envp)
		return (MALLOC_FAIL);
	i = -1;
	while (envp[++i])
		envp_to_ms_envp(envp[i], &ms_env->ms_envp[i]);
	if (!ms_envp_key("OLDPWD", ms_env->ms_envp))
	{
		ms_env->ms_envp->key = ft_strdup("OLDPWD");
		if (!ms_env->ms_envp->key)
			return (MALLOC_FAIL);
	}
	return (NO_ERROR);
}

//  initialize minishell
// t_err	ms_init(char **envp, t_env *envi)
// {
// 	if (init_ms_env(envp, envi) == MALLOC_FAIL)
// 		return (MALLOC_FAIL);
// 	if (ms_envp_to_var(envi->ms_envp, &envi->envp) == MALLOC_FAIL)
// 		return (MALLOC_FAIL);
// 	if (update_shlvl(envi) == MALLOC_FAIL)
// 		return (MALLOC_FAIL);
// 	save_term_settings(&envi->termios_p);
// 	return (NO_ERROR);

// 	if (init_ms_env(envp, envi) != MALLOC_FAIL)
// 		if (ms_envp_to_var(envi->ms_envp, &envi->envp) != MALLOC_FAIL)
// 			if (update_shlvl(envi) != MALLOC_FAIL)
// 				return (NO_ERROR | tcgetattr(2, &envi->termios_p));
// 	return (MALLOC_FAIL);
// }

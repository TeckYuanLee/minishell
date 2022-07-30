#include "minishell.h"

//  add keys and values into envp
t_err	add_to_ms_envp(char *key, char *value, t_ms_envp **head)
{
	t_ms_envp	*envp;
	t_ms_envp	*new_envp;
	int			i;

	i = 0;
	envp = *head;
	while ((&envp[i])->key)
		i++;
	new_envp = ft_calloc(i + 2, sizeof(t_ms_envp));
	if (!new_envp)
		return (MALLOC_FAIL);
	i = 0;
	while (envp[i].key)
	{
		new_envp[i].key = envp[i].key;
		new_envp[i].value = envp[i].value;
		i++;
	}
	new_envp[i].key = key;
	new_envp[i].value = value;
	free(*head);
	*head = new_envp;
	return (NO_ERROR);
}

//  replace env value
t_err	replace_value(char *key, char *value, t_ms_envp *envp)
{
	int	i;

	i = 0;
	while (envp[i].key)
	{
		if (ft_strncmp(envp[i].key, key, ft_strlen(key) + 1) == 0)
		{
			if (envp[i].value)
				free(envp[i].value);
			envp[i].value = value;
			break ;
		}
		i++;
	}
	return (NO_ERROR);
}

//  get env key
t_err	get_env_key(const char *str, char **return_key)
{
	int		i;

	*return_key = NULL;
	i = 0;
	if (ft_isdigit(*str))
		return (KEY_ERR);
	while (char_is_allowed(str[i], "$()<>'/\\;=.\0") && !ft_isspace(str[i]))
		i++;
	*return_key = ft_calloc(i + 1, 1);
	if (!*return_key)
		return (MALLOC_FAIL);
	ft_strlcpy(*return_key, str, i + 1);
	return (NO_ERROR);
}

//  get env value
t_err	get_env_value(t_ms_envp *envp, char *key, char **value_ptr)
{
	int		i;

	i = 0;
	while (envp[i].key)
	{
		if (!(ft_strncmp(envp[i].key, key, ft_strlen(key) + 1)))
		{
			if (envp[i].value)
			{
				*value_ptr = ft_strdup(envp[i].value);
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
		i++;
	}
	*value_ptr = NULL;
	return (NO_KEY);
}

//  join env key and value
t_err	combine_key_value(t_ms_envp *ms_envp, char **var)
{
	char	*intermediate;
	char	*combined;

	if (ms_envp->value)
	{
		intermediate = ft_strjoin(ms_envp->key, "=");
		if (!intermediate)
			return (MALLOC_FAIL);
		combined = ft_strjoin(intermediate, ms_envp->value);
		free (intermediate);
		if (!combined)
			return (MALLOC_FAIL);
	}
	else
		combined = ft_strdup(ms_envp->key);
	if (!combined)
		return (MALLOC_FAIL);
	*var = combined;
	return (NO_ERROR);
}

//  add 'oldpwd' to envp key
t_err	add_empty_oldpwd(t_ms_envp *ms_envp)
{
	ms_envp->key = ft_strdup("OLDPWD");
	if (!ms_envp->key)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

//  check if key of envp exists
t_bool	key_exists(char *key, t_ms_envp *ms_envp)
{
	int	key_len;

	if (!ms_envp)
		return (printf(BHRED "[key_exists] ms_envp pointing to NULL?!\n" BHWHT));
	key_len = ft_strlen(key);
	while (ms_envp->key)
	{
		if (ft_strncmp(ms_envp->key, key, key_len + 1) == 0)
			return (TRUE);
		ms_envp++;
	}
	return (FALSE);
}

//  copy from env key and value to envp
t_err	copy_to_ms_envp(char *str, t_ms_envp *custom_envp)
{
	char	*key;
	char	*value;

	if (!str)
		return (printf(BHRED "[copy_to_custom_envp] str to NULL..\n" BHWHT));
	if (get_env_key(str, &key) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ft_strlen(key) < ft_strlen(str))
	{
		if (str[ft_strlen(key)] != '=')
			return (printf(BHRED "[copy_to_custom_envp] no '=' sign..\n" BHWHT));
		value = ft_strdup(str + ft_strlen(key) + 1);
		if (!value)
		{
			free (key);
			return (MALLOC_FAIL);
		}
	}
	else
		value = NULL;
	custom_envp->key = key;
	custom_envp->value = value;
	return (NO_ERROR);
}

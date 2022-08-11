#include "minishell.h"

//  check if key of envp exists ///// ok
t_bool	ms_envp_key(char *key, t_item *ms_envp)
{
	int	key_len;

	if (!ms_envp)
		return (printf(BHRED "[ms_envp_key] ms_envp pointing to NULL?!\n" BHWHT));
	key_len = ft_strlen(key);
	while (ms_envp->key)
	{
		if (ft_strncmp(ms_envp->key, key, key_len + 1) == 0)
			return (TRUE);
		ms_envp++;
	}
	return (FALSE);
}

//  replace env value /////
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

//  join env key and value /////
t_err	combine_key_value(t_item *ms_envp, char **var)
{
	char	*temp;
	char	*joined;

	if (ms_envp->value)
	{
		temp = ft_strjoin(ms_envp->key, "=");
		if (!temp)
			return (MALLOC_FAIL);
		joined = ft_strjoin(temp, ms_envp->value);
		free (temp);
	}
	else
		joined = ft_strdup(ms_envp->key);
	if (!joined)
		return (MALLOC_FAIL);
	*var = joined;
	return (NO_ERROR);
}

//  get env value /////
t_err	get_env_value(t_item *ms_envp, char *key, char **value_ptr)
{
	int		i;

	i = -1;
	while (ms_envp[++i].key)
	{
		if (!(ft_strncmp(ms_envp[i].key, key, ft_strlen(key) + 1)))
		{
			if (ms_envp[i].value)
			{
				*value_ptr = ft_strdup(ms_envp[i].value);
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

//	get env key /////
t_err	get_env_key(const char *str, char **return_key)
{
	int		i;

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

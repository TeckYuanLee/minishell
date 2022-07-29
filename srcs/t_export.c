#include "minishell.h"

t_err	add_value_to_envp(t_ms_envp **ms_envp, char *key, char *value)
{
	if (!key_exists(key, *ms_envp))
	{
		if (add_to_ms_envp(key, value, ms_envp) == MALLOC_FAIL)
		{
			free(key);
			return (MALLOC_FAIL);
		}
		return (NO_ERROR);
	}
	replace_value(key, value, *ms_envp);
	free (key);
	return (NO_ERROR);
}

t_err	get_plusis_value(char *value, char *key, t_ms_envp *ms_envp, \
		char **joined)
{
	char	*old_value;
	char	*temp;

	temp = NULL;
	if (get_env_value(ms_envp, key, &old_value) == MALLOC_FAIL)
	{
		free(key);
		free(value);
		return (MALLOC_FAIL);
	}
	if (old_value && value)
	{
		temp = ft_strjoin(old_value, value);
		ft_free_str(&old_value);
		ft_free_str(&value);
		if (!temp)
			return (MALLOC_FAIL);
	}
	else if (!old_value)
		temp = value;
	*joined = temp;
	return (NO_ERROR);
}

char	*point_to_value(char *str)
{
	str = ft_strchr(str, '=');
	if (str)
		str++;
	return (str);
}

t_err	parse_and_add_to_envp(char *str, t_ms_envp **ms_envp, char *key)
{
	char	*value;

	value = NULL;
	if (str[ft_strlen(key)] == '=' || str[ft_strlen(key)] == '+')
	{
		value = ft_strdup(point_to_value(str));
		if (!value)
		{
			free(key);
			return (MALLOC_FAIL);
		}
	}
	if (str[ft_strlen(key)] == '+')
		if (get_plusis_value(value, key, *ms_envp, &value) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	if (str[ft_strlen(key)] == '=' || str[ft_strlen(key)] == '\0')
		return (add_value_to_envp(ms_envp, key, value));
	return (NO_ERROR);
}

int	export_error_msg(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		ft_putstr_fd("minishell: export: -", 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value] ...]\n", 2);
		return (2);
	}
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	is_export_key(char *key)
{
	size_t	i;

	i = 0;
	if (!key || !*key)
		return (0);
	if (ft_isdigit(key[0]) || key[0] == '-')
		return (0);
	while (key[i] && char_is_allowed(key[i], "'=\"-#+^~.|&@!;()<>*\\"))
		i++;
	if (ft_strlen(key) == i)
		return (1);
	return (0);
}

t_err	export_get_env_key(const char *str, char **return_key)
{
	int		i;

	*return_key = NULL;
	i = 0;
	if (ft_isdigit(*str))
		return (KEY_ERR);
	while (char_is_allowed(str[i], "=+\0") && !ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '=')
		return (KEY_ERR);
	*return_key = ft_calloc(i + 1, 1);
	if (!*return_key)
		return (MALLOC_FAIL);
	ft_strlcpy(*return_key, str, i + 1);
	return (NO_ERROR);
}

t_err	single_export(t_ms_envp *ms_envp)
{
	int	arr_len;
	int	*arr;

	arr_len = get_ms_envp_len(ms_envp);
	if (!ms_envp)
		return (printf(RED "[single_export] ms_envp pointing to (null)..\n"));
	arr = ft_calloc(arr_len, sizeof(int));
	if (!arr)
		return (MALLOC_FAIL);
	while (not_ready(arr, arr_len))
	{
		if (print_smallest_and_mark_arr(ms_envp, arr, arr_len) == MALLOC_FAIL)
		{
			free(arr);
			return (MALLOC_FAIL);
		}
	}
	free(arr);
	return (0);
}

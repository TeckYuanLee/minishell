#include "minishell.h"

//	if key doesn't exist, add to envp, else update value
t_err	add_value_to_envp(t_item **item, char *key, char *value)
{
	if (!ms_envp_key(key, *item))
	{
		if (add_to_ms_envp(key, value, item) == MALLOC_FAIL)
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
t_err	get_plusis_value(char *value, char *key, t_item *item, \
		char **joined)
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

//	extract value and add to list of envp
t_err	parse_and_add_to_envp(char *str, t_item **item, char *key)
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
		if (get_plusis_value(value, key, *item, &value) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	if (str[ft_strlen(key)] == '=' || str[ft_strlen(key)] == '\0')
		return (add_value_to_envp(item, key, value));
	return (NO_ERROR);
}

//	identify if it is an export key
int	is_export_key(char *key)
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
t_err	export_get_env_key(const char *str, char **return_key)
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
t_err	single_export(t_item *item)
{
	int	arr_len;
	int	*arr;

	arr_len = 0;
	while (item->key)
	{
		item++;
		arr_len++;
	}
	if (!item)
		return (printf(BHRED "[single_export] item pointing to (null)..\n"));
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
int	ms_export(char **argv, t_env *envi)
{
	int		i;
	char	*key;
	int		exitcode;

	if (!argv[1])
		return (single_export(envi->item));
	exitcode = 0;
	i = 0;
	while (argv[++i])
	{
		if (export_get_env_key(argv[i], &key) == MALLOC_FAIL)
			return (-1);
		if (!is_export_key(key))
		{
			ft_free_str(&key);
			exitcode = export_error_msg(argv[i]);
		}
		else
			parse_and_add_to_envp(argv[i], &envi->item, key);
	}
	if (ms_envp_to_var(envi->item, &envi->envp) == MALLOC_FAIL)
		return (-1);
	return (exitcode);
}

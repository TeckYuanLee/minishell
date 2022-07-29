#include "minishell.h"

t_hard_strings	init_strings(void)
{
	t_hard_strings	strings;

	strings.oldpwd = ft_strdup("OLDPWD");
	if (strings.oldpwd)
		strings.pwd = ft_strdup("PWD");
	if (!strings.pwd)
	{
		free(strings.oldpwd);
		strings.oldpwd = NULL;
	}
	return (strings);
}

int	add_path_chunk(char parse_path[512], char *path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 1024 && parse_path[i])
		i++;
	if (i != 0 && parse_path[i - 1] != '/')
	{
		parse_path[i] = '/';
		i++;
	}
	while (path[j] && path[j] != '/')
	{
		parse_path[i] = path[j];
		i++;
		j++;
	}
	return (j);
}

void	remove_dir(char parse_path[512])
{
	int	i;

	i = 0;
	while (i < 255 && parse_path[i])
		i++;
	while (parse_path[i] != '/')
	{
		parse_path[i] = '\0';
		i--;
	}
	parse_path[i] = '\0';
}

void	copy_or_rm(t_ms_envp **envp, char *key, t_ms_envp **new_envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*envp)[i].key)
	{
		if (ft_strncmp((*envp)[i].key, key, ft_strlen(key) + 1))
		{
			(*new_envp)[j].key = (*envp)[i].key;
			(*new_envp)[j].value = (*envp)[i].value;
			j++;
		}
		else
		{
			free((*envp)[i].key);
			free((*envp)[i].value);
		}
		i++;
	}
}

t_err	rm_from_envp(char *key, t_ms_envp **envp)
{
	t_ms_envp	*new_envp;
	int			i;

	i = 0;
	while ((*envp)[i].key)
		i++;
	new_envp = ft_calloc(i + 1, sizeof(t_ms_envp));
	if (!new_envp)
		return (MALLOC_FAIL);
	copy_or_rm(envp, key, &new_envp);
	free(*envp);
	*envp = new_envp;
	return (NO_ERROR);
}

int	unset_error_msg(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		ft_putstr_fd("minishell: unset: -", 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("unset: usage: unset [name ...]\n", 2);
		return (2);
	}
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	is_unset_key(char *key)
{
	size_t	i;

	i = 0;
	if (!key)
		return (0);
	if (ft_isdigit(key[0]) || key[0] == '-')
		return (0);
	while (key[i] && char_is_allowed(key[i], "/\\;.+=-{}*#@!^~"))
		i++;
	if (ft_strlen(key) == i)
		return (1);
	return (0);
}

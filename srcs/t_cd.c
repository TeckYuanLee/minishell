#include "minishell.h"

//	replace values of both old and new pwd
t_err	update_both_pwds(t_env *envi, char *curr_pwd, char *new_pwd)
{
	t_pwdstr	strings;

	strings = init_strings();
	if (!strings.pwd)
		return (MALLOC_FAIL);
	if (key_exists("PWD", envi->ms_envp))
	{
		update_value(strings.pwd, new_pwd, envi->ms_envp);
		free(strings.pwd);
	}
	else
		if (add_to_ms_envp(strings.pwd, new_pwd, &envi->ms_envp) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	if (key_exists("OLDPWD", envi->ms_envp))
	{
		update_value(strings.oldpwd, curr_pwd, envi->ms_envp);
		free(strings.oldpwd);
		return (NO_ERROR);
	}
	else if (add_to_ms_envp(strings.oldpwd, curr_pwd, &envi->ms_envp) == 1)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

//	combine old pwd with path
char	*parse_path(char *path, char *old_pwd)
{
	int			i;
	char		parse_path[512];

	ft_bzero(&parse_path, 512);
	ft_strlcpy(parse_path, old_pwd, ft_strlen(old_pwd) + 1);
	i = 0;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.')
		{
			remove_dir(parse_path);
			i += 2;
		}
		else if (path[i] == '.' && path[i + 1] == '/')
			i += 2;
		else if (path[i] == '/')
			i++;
		else if (ft_isprint(path[i]))
			i += add_path_chunk(parse_path, &path[i]);
		else
			printf(BHRED "[parse_path] something rly wrong..." BHWHT);
	}
	return (ft_strdup(parse_path));
}

//	update old pwd with current pwd
t_err	only_update_oldpwd(t_env *envi, char *curr_pwd)
{
	char	*key;

	key = NULL;
	if (key_exists("OLDPWD", envi->ms_envp))
		return ((t_err)update_value("OLDPWD", curr_pwd, envi->ms_envp));
	key = ft_strdup("OLDPWD");
	if (!key)
		return (MALLOC_FAIL);
	return (add_to_ms_envp(key, curr_pwd, &envi->ms_envp));
}

//	join two strings together
int	add_string2(char *perror_str, char *string2, int rv)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(perror_str, ": ");
	free (perror_str);
	if (!temp)
		return (-1);
	temp2 = ft_strjoin(temp, string2);
	free(temp);
	if (!temp2)
		return (-1);
	perror(temp2);
	free(temp2);
	return (rv);
}

//	update current pwd and new pwd values
t_err	update_pwd_oldpwd(char *path, t_env *envi)
{
	char	*new_pwd;
	char	*curr_pwd;

	if (get_env_value(envi->ms_envp, "PWD", &curr_pwd) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (!ft_strncmp(path, ".", 2))
		return (only_update_oldpwd(envi, curr_pwd));
	if (path[0] == '/')
		new_pwd = ft_strdup(path);
	else
		new_pwd = parse_path(path, curr_pwd);
	if (!new_pwd)
	{
		free(curr_pwd);
		return (MALLOC_FAIL);
	}
	update_both_pwds(envi, curr_pwd, new_pwd);
	return (NO_ERROR);
}

//	execute perror
int	ms_perror(char *perror_str, char *string, char *string2, int rv)
{
	char	*temp;
	char	*temp2;

	if (perror_str)
	{
		if (string)
		{
			temp = ft_strjoin(perror_str, ": ");
			if (!temp)
				return (-1);
			temp2 = ft_strjoin(temp, string);
			free(temp);
			if (!temp2)
				return (-1);
			if (string2)
				return (add_string2(temp2, string2, rv));
			perror(temp2);
			free(temp2);
		}
		else
			perror(perror_str);
	}
	return (rv);
}

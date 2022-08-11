#include "minishell.h"

//	initialize pwd strings
t_pwd	init_strings(void)
{
	t_pwd	strings;

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

//	replace values of both old and new pwd
t_err	update_both_pwds(t_env *envi, char *curr_pwd, char *new_pwd)
{
	t_pwd	strings;

	strings = init_strings();
	if (!strings.pwd)
		return (MALLOC_FAIL);
	if (ms_envp_key("PWD", envi->item))
	{
		update_value(strings.pwd, new_pwd, envi->item);
		free(strings.pwd);
	}
	else
		if (add_to_ms_envp(strings.pwd, new_pwd, &envi->item) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	if (ms_envp_key("OLDPWD", envi->item))
	{
		update_value(strings.oldpwd, curr_pwd, envi->item);
		free(strings.oldpwd);
		return (NO_ERROR);
	}
	else if (add_to_ms_envp(strings.oldpwd, curr_pwd, &envi->item) == 1)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

//	copy path contents to parse path
int	add_path_chunk(char parse_path[512], char *path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 1024 && parse_path[i])
		i++;
	if (i && parse_path[i - 1] != '/')
		parse_path[i++] = '/';
	while (path[j] && path[j] != '/')
		parse_path[i++] = path[j++];
	return (j);
}

//	remove parse path contents
void	remove_dir(char parse_path[512])
{
	int	i;

	i = 0;
	while (i < 255 && parse_path[i])
		i++;
	while (parse_path[i] != '/')
		parse_path[i--] = '\0';
	parse_path[i] = '\0';
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
	if (ms_envp_key("OLDPWD", envi->item))
		return ((t_err)update_value("OLDPWD", curr_pwd, envi->item));
	key = ft_strdup("OLDPWD");
	if (!key)
		return (MALLOC_FAIL);
	return (add_to_ms_envp(key, curr_pwd, &envi->item));
}

//	update current pwd and new pwd values
t_err	update_pwd_oldpwd(char *path, t_env *envi)
{
	char	*new_pwd;
	char	*curr_pwd;

	if (get_env_value(envi->item, "PWD", &curr_pwd) == MALLOC_FAIL)
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

//	handle cd command
t_err	ms_cd(char **argv, t_env *envi)
{
	if (!argv)
		return (printf(BHRED "[ms_cd] NULL-pointing argv..\n" BHWHT));
	if (!*argv)
		return (printf(BHRED "[ms_cd] empty argv..\n" BHWHT));
	if (!argv[1])
		return (0);
	if (chdir(argv[1]))
		return (ms_perror("Minishell: cd", argv[1], NULL, 1));
	if (update_pwd_oldpwd(argv[1], envi) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ms_envp_to_var(envi->item, &envi->envp) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

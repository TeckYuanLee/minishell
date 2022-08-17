/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:26:52 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:26:52 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//	combine old pwd with path
char	*parse_path(char *path, char *old_pwd)
{
	int		i;
	char	parse_path[512];

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
	}
	return (ft_strdup(parse_path));
}

//	update old pwd with current pwd
t_err	only_update_oldpwd(t_env *ms_env, char *curr_pwd)
{
	char	*key;

	key = NULL;
	if (ms_env_key("OLDPWD", ms_env->item))
		return ((t_err)update_value("OLDPWD", curr_pwd, ms_env->item));
	key = ft_strdup("OLDPWD");
	if (!key)
		return (MALLOC_FAIL);
	return (update_ms_env(key, curr_pwd, &ms_env->item));
}

//	update current pwd and new pwd values
t_err	update_pwd_oldpwd(char *path, t_env *ms_env)
{
	char	*new_pwd;
	char	*curr_pwd;

	if (get_env_value(ms_env->item, "PWD", &curr_pwd) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (!ft_strncmp(path, ".", 2))
		return (only_update_oldpwd(ms_env, curr_pwd));
	if (path[0] == '/')
		new_pwd = ft_strdup(path);
	else
		new_pwd = parse_path(path, curr_pwd);
	if (!new_pwd)
	{
		free(curr_pwd);
		return (MALLOC_FAIL);
	}
	if (ms_env_key("PWD", ms_env->item))
		update_value("PWD", new_pwd, ms_env->item);
	else if (update_ms_env("PWD", new_pwd, &ms_env->item) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ms_env_key("OLDPWD", ms_env->item))
		return (update_value("OLDPWD", curr_pwd, ms_env->item));
	else if (update_ms_env("OLDPWD", curr_pwd, &ms_env->item) == 1)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

//	handle cd command
t_err	ms_cd(char **argv, t_env *ms_env)
{
	if (!argv[1])
		return (0);
	if (chdir(argv[1]))
		return (ms_perror("Minishell: cd", argv[1], NULL, 1));
	if (update_pwd_oldpwd(argv[1], ms_env) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ms_env_to_envp(ms_env->item, &ms_env->envp) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

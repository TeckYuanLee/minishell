/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:28:19 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:28:19 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	make edits to the paths
char	**ft_edit_paths(char **paths, char **arg, int i)
{
	char	**exec_paths;
	char	*extension;
	int		j;

	exec_paths = (char **)malloc(sizeof(char *) * (i + 1));
	if (!exec_paths)
		return (ft_free_paths(paths, NULL, NULL));
	j = 0;
	extension = ft_strjoin("/", arg[0]);
	if (!extension)
		return (ft_free_paths(paths, exec_paths, NULL));
	while (paths[j])
	{
		exec_paths[j] = ft_strjoin(paths[j], extension);
		if (!exec_paths[j])
			return (ft_free_paths(paths, exec_paths, extension));
		j++;
	}
	exec_paths[j] = NULL;
	ft_free_paths(paths, NULL, extension);
	return (exec_paths);
}

//	check for dir input commands
int	ft_parse_dir(char **envp, char **arg, t_env *ms_env, char **paths)
{
	if (!ft_strncmp(arg[0], ".", 2))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		free_envi(ms_env, -100);
		ft_free_paths(paths, NULL, NULL);
		exit(2);
	}
	if ((!ft_strncmp(arg[0], "/", 1)) || (!ft_strncmp(arg[0], "./", 2))
		|| (!ft_strncmp(arg[0], "../", 3)))
		if (ft_parse_dir_loop(arg[0]))
			ft_dir_exit(arg, ms_env, paths);
	if ((!ft_strncmp(arg[0], "/", 1)) || (!ft_strncmp(arg[0], "./", 2))
		|| (!ft_strncmp(arg[0], "../", 3)))
		ft_is_dir(envp, arg, ms_env, paths);
	if (!ft_strncmp(arg[0], "..", 3))
	{
		ft_free_paths(paths, NULL, NULL);
		ft_cmd_exit(arg, ms_env, NULL);
	}
	return (0);
}

//	check access and execute command
int	ft_acces_and_exec(t_env *ms_env, char **arg, char **paths)
{
	char	**exec_paths;
	char	*path;
	int		i;

	i = 0;
	exec_paths = NULL;
	ft_parse_dir(ms_env->envp, arg, ms_env, paths);
	while (paths && paths[i])
		i++;
	if (paths)
		exec_paths = ft_edit_paths(paths, arg, i);
	if (!exec_paths)
		ft_error_exec(5, 0, ms_env);
	path = ft_search_bins(exec_paths);
	if (path)
	{
		i = ft_check_access(path, ms_env->envp, arg, ms_env);
		if (execve(path, arg, ms_env->envp) < 0)
			ft_error_exec(4, 0, ms_env);
	}
	ft_free_paths(exec_paths, NULL, NULL);
	if (!path)
		ft_cmd_exit(arg, ms_env, paths);
	return (0);
}

//	find path from env
char	*find_path_env(char **envp, t_env *ms_env)
{
	int		i;
	int		len;
	char	*temp;
	char	*path;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (!(ft_strncmp(envp[i], "PATH", 4)))
		{
			len = ft_strlen(envp[i]);
			temp = (char *)malloc(sizeof(char) * (len + 1));
			if (!temp)
				ft_error_exec(5, 0, ms_env);
			temp = ft_memcpy(temp, envp[i], ft_strlen(envp[i]));
			temp[len] = '\0';
			path = ft_strtrim(temp, "PATH=");
			free (temp);
			return (path);
		}
	}
	return (NULL);
}

//	get path from env then access and execute
int	ft_get_paths(t_env *ms_env, char **arg)
{
	char	*path;
	char	**paths;

	paths = NULL;
	path = find_path_env(ms_env->envp, ms_env);
	if (path)
	{
		paths = ft_split(path, ':');
		free (path);
	}
	else
		paths = ft_split("", ' ');
	if (!paths)
		ft_error_exec(5, 0, ms_env);
	ft_acces_and_exec(ms_env, arg, paths);
	return (0);
}

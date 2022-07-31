#include "minishell.h"

//	check for dir input commands
int	ft_parse_dir(char **envp, char **arg, t_env *envi, char **paths)
{
	if (!ft_strncmp(arg[0], ".", 2))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		free_envi(envi);
		ft_free_paths(paths, NULL, NULL);
		exit(2);
	}
	if ((!ft_strncmp(arg[0], "/", 1)) || (!ft_strncmp(arg[0], "./", 2))
		|| (!ft_strncmp(arg[0], "../", 3)))
		if (ft_parse_dir_loop(arg[0]))
			ft_dir_exit(arg, envi, paths);
	if ((!ft_strncmp(arg[0], "/", 1)) || (!ft_strncmp(arg[0], "./", 2))
		|| (!ft_strncmp(arg[0], "../", 3)))
		ft_is_dir(envp, arg, envi, paths);
	if (!ft_strncmp(arg[0], "..", 3))
	{
		ft_free_paths(paths, NULL, NULL);
		ft_cmd_exit(arg, envi, NULL);
	}
	return (0);
}

//	check access and execute command
int	ft_acces_and_exec(t_env *envi, char **arg, char **paths)
{
	char	**exec_paths;
	char	*path;
	int		i;

	i = 0;
	exec_paths = NULL;
	ft_parse_dir(envi->var, arg, envi, paths);
	while (paths && paths[i])
		i++;
	if (paths)
		exec_paths = ft_edit_paths(paths, arg, i);
	if (!exec_paths)
		ft_error_exec(5, 0, envi);
	path = ft_search_bins(exec_paths);
	if (path)
	{
		i = ft_check_access(path, envi->var, arg, envi);
		ft_exec_cmd(path, envi->var, arg, envi);
	}
	ft_free_paths(exec_paths, NULL, NULL);
	if (!path)
		ft_cmd_exit(arg, envi, paths);
	return (0);
}

//	find path from env
char	*find_path_env(char **envp, t_env *envi)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!(ft_strncmp(envp[i], "PATH", 4)))
		{
			len = ft_strlen(envp[i]);
			temp = (char *)malloc(sizeof(char) * (len + 1));
			if (!temp)
				ft_error_exec(5, 0, envi);
			temp = ft_memcpy(temp, envp[i], ft_strlen(envp[i]));
			temp[len] = '\0';
			return (get_path_env(temp));
		}
		i++;
	}
	return (NULL);
}

//	get path from env then access and execute
int	ft_get_paths(t_env *envi, char **arg)
{
	char	*path;
	char	**paths;

	paths = NULL;
	path = find_path_env(envi->var, envi);
	if (path)
	{
		paths = ft_split(path, ':');
		free (path);
	}
	else
		paths = ft_split("", ' ');
	if (!paths)
		ft_error_exec(5, 0, envi);
	ft_acces_and_exec(envi, arg, paths);
	return (0);
}

//	start of nopipe instructions
void	ft_helper_nopipe_start(t_tree *tree, t_env *envi)
{
	if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
	{
		free_envi(envi);
		exit(0);
	}
	ft_check_builtin(tree, envi);
	ft_get_paths(envi, tree->data);
}

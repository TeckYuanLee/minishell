#include "minishell.h"

//	execute directory if it exists
int	ft_is_dir(char **envp, char **arg, t_envi *envi, char **paths)
{
	struct stat	f;
	int			flag;

	if (lstat(arg[0], &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (flag == S_IFDIR)
			ft_dir_exit(arg, envi, paths);
		else if (flag == S_IFREG)
		{
			ft_check_access(arg[0], envp, arg, envi);
			ft_exec_cmd(arg[0], envp, arg, envi);
		}
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": no such file or directory\n", 2);
	ft_free_paths(paths, NULL, NULL);
	free_envi(envi);
	exit(127);
	return (0);
}

//	check if directory or file
void	ft_dir_exit(char **arg, t_envi *envi, char **paths)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": is a directory\n", 2);
	free_envi(envi);
	ft_free_paths(paths, NULL, NULL);
	exit(126);
}

//	look for alphabets
int	ft_parse_dir_loop(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]))
			return (0);
	return (1);
}

//	error message for command not found
void	ft_cmd_exit(char **arg, t_envi *envi, char **paths)
{
	(void)paths;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_envi(envi);
	exit(127);
}

//	free all paths
void	*ft_free_paths(char **first, char **second, char *third)
{
	int	i;

	i = 0;
	if (first[i])
		while (first[i])
			free(first[i++]);
	free (first);
	first = NULL;
	if (third)
		free (third);
	if (second)
		ft_free_paths(second, NULL, NULL);
	return (NULL);
}

//	execute command
int	ft_exec_cmd(char *path, char **envp, char **arg, t_envi *envi)
{
	if (execve(path, arg, envp) < 0)
		ft_error_exec(4, 0, envi);
	return (0);
}

//	check if have permission to execute
int	ft_check_access(char *path, char **envp, char **arg, t_envi *envi)
{
	int	check;

	check = access(path, X_OK);
	if (check != 0 && arg && envp)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_envi(envi);
		exit(126);
	}
	return (check);
}

//	return information on file status
char	*ft_search_bins(char **exec_paths)
{
	struct stat	stat;
	int			i;

	i = 0;
	while (exec_paths && exec_paths[i])
	{
		if (!(lstat(exec_paths[i], &stat)))
			return (exec_paths[i]);
		i++;
	}
	return (NULL);
}

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

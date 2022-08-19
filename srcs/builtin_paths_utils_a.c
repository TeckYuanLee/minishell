/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_paths_utils_a.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:27:33 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:27:33 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	execute directory if it exists
int	is_dir(char **envp, char **arg, t_env *ms_env, char **paths)
{
	struct stat	f;
	int			flag;

	if (lstat(arg[0], &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (flag == S_IFDIR)
			dir_exit(arg, ms_env, paths);
		else if (flag == S_IFREG)
		{
			check_access(arg[0], envp, arg, ms_env);
			if (execve(arg[0], arg, envp) < 0)
				exec_error(4, 0, ms_env);
		}
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_paths(paths, NULL, NULL);
	free_envi(ms_env, 127);
	return (0);
}

//	check if directory or file
void	dir_exit(char **arg, t_env *ms_env, char **paths)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": is a directory\n", 2);
	free_envi(ms_env, -100);
	free_paths(paths, NULL, NULL);
	exit(126);
}

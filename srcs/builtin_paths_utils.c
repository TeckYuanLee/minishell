/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_paths_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:27:36 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:27:36 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	look for alphabets
int	parse_dir_utils(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]))
			return (0);
	return (1);
}

//	error message for command not found
void	cmd_not_found(char **arg, t_env *ms_env, char **paths)
{
	(void)paths;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_envi(ms_env, 127);
}

//	free all paths
void	*free_paths(char **first, char **second, char *third)
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
		free_paths(second, NULL, NULL);
	return (NULL);
}

//	check if have permission to execute
int	check_access(char *path, char **envp, char **arg, t_env *ms_env)
{
	int	check;

	check = access(path, X_OK);
	if (check != 0 && arg && envp)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": permission denied\n", 2);
		free_envi(ms_env, 126);
	}
	return (check);
}

//	return information on file status
char	*search_bins(char **exec_paths)
{
	struct stat	stat;
	int			i;

	i = -1;
	while (exec_paths && exec_paths[++i])
		if (!(lstat(exec_paths[i], &stat)))
			return (exec_paths[i]);
	return (NULL);
}

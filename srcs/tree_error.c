/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:31:57 by telee             #+#    #+#             */
/*   Updated: 2022/08/19 17:01:00 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	print error message for unset
int	unset_error_msg(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		ft_putstr_fd("minishell: unset: -", 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": option (unsupported)\n", 2);
		return (2);
	}
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

//	print error message for export command
int	export_error_msg(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		ft_putstr_fd("minishell: export: -", 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": option (unsupported)\n", 2);
		return (2);
	}
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

//	lnr angles usage error message
int	redir_error(t_tree *tree, int fd, t_env *ms_env)
{
	if (fd == 100)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tree->data[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_envi(ms_env, 1);
	}
	else
	{
		close(fd);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tree->data[0], 2);
		ft_putstr_fd(": permission denied\n", 2);
		free_envi(ms_env, 1);
	}
	return (-1);
}

//	function execution error message
int	exec_error(int code, int *fd, t_env *ms_env)
{
	if (fd != 0)
		close(*fd);
	free_envi(ms_env, -100);
	ft_putstr_fd("minishell:", 2);
	if (code == 1)
		ft_putstr_fd("fork error\n", 2);
	else if (code == 3)
		ft_putstr_fd("pipe error\n", 2);
	if (code >= 1 && code <= 3)
		exit(71);
	if (code == 4)
	{
		exit(0);
	}
	else if (code == 5)
		ft_putstr_fd("malloc error\n", 2);
	else if (code == 6)
		ft_putstr_fd("access error\n", 2);
	exit(1);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:27:23 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:27:23 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	echo readline
int	print_echo(t_tree *tree, int i, int err)
{
	int	j;

	while (tree->data[i])
	{
		j = ft_strlen(tree->data[i]);
		err = write(STDOUT_FILENO, tree->data[i], j);
		if (tree->data[i + 1] && err != -1)
			err = write(STDOUT_FILENO, " ", 1);
		if (err == -1)
			return (err);
		i++;
	}
	return (err);
}

//	check if there is '-n' for echo
int	handle_echo(t_tree *tree, int i, int check, int err)
{
	int	ret;
	int	j;

	ret = 0;
	while (tree->data[i] && !(ft_strncmp(tree->data[i], "-n", 2)) && err == 0)
	{
		check++;
		j = -1;
		while (tree->data[i][++j] && tree->data[i][j + 1] && ret == 0)
			if (tree->data[i][j + 1] != 'n')
				ret = 1;
		if (ret)
			break ;
		i++;
	}
	err = print_echo(tree, i, err);
	if (err == -1)
		return (err);
	if (!check)
		err = write(STDOUT_FILENO, "\n", 1);
	return (err);
}

//	execute echo command
int	builtin_echo(t_env *ms_env, t_tree *tree)
{
	int	i;
	int	check;
	int	err;

	i = 1;
	check = 0;
	err = handle_echo(tree, i, check, 0);
	if (err == -1)
	{
		ft_putstr_fd("minishell: error in echo.\n", 2);
		ms_env->exitcode = 1;
	}
	else
		ms_env->exitcode = 0;
	return (1);
}

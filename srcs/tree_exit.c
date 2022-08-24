/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:32:34 by telee             #+#    #+#             */
/*   Updated: 2022/08/24 17:14:14 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	handle exit command
int	exit_cmd(t_tree *tree, t_env *ms_env)
{
	int	i;

	i = 0;
	while (tree->data[i])
		i++;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i == 1)
	{
		ft_putstr_fd("exit\n", 2);
		ms_env->exitcode = 0;
		free_envi(ms_env, ms_env->exitcode);
	}
	exit_multi_arg(tree, ms_env, i);
	exit_one_arg(tree, ms_env, i);
	return (ms_env->exitcode);
}

//	exit if data is long long max, else if range greater long long max
void	exit_one_range(t_tree *tree, t_env *ms_env)
{
	size_t	range;

	range = atoi_exit(tree->data[1]);
	if (!(ft_strcmp(tree->data[1], "9223372036854775807")))
	{
		ms_env->exitcode = (atoi_exit(tree->data[1]) % 256);
		ft_putstr_fd("exit\n", 2);
		free_envi(ms_env, ms_env->exitcode);
	}
	else if (!(ft_strcmp(tree->data[1], "9223372036854775808"))
		|| !(ft_strcmp(tree->data[1], "-9223372036854775809")))
		exit_numeric(tree, ms_env, 'c');
	else if (!(ft_strcmp(tree->data[1], "-9223372036854775807")))
		exit_numeric(tree, ms_env, 'd');
	else if (!(ft_strcmp(tree->data[1], "-9223372036854775808")))
		exit_numeric(tree, ms_env, 'e');
	else if (range > 9223372036854775806)
		exit_numeric(tree, ms_env, 'z');
}

//	handle exit with only one argument
void	exit_one_arg(t_tree *tree, t_env *ms_env, int i)
{
	int	check;

	check = 0;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i == 2)
	{
		check = check_signs(tree->data[1]);
		if (check_isalpha(tree->data[1]) || check > 1)
			exit_numeric(tree, ms_env, 'a');
		else if (!check_isdigit(tree->data[1]) && check == 1)
			exit_numeric(tree, ms_env, 'b');
		exit_one_range(tree, ms_env);
		if (check == 1 && !(tree->data[1][0] == '+'))
		{
			check = (atoi_exit(tree->data[1]) % 256);
			ms_env->exitcode = 256 - check;
			// ft_putstr_fd("exit\n", 2);
			free_envi(ms_env, ms_env->exitcode);
		}
		else if (check == 0 || (tree->data[1][0] == '+'))
		{
			ms_env->exitcode = (atoi_exit(tree->data[1]) % 256);
			ft_putstr_fd("exit\n", 2);
			free_envi(ms_env, ms_env->exitcode);
		}
	}
}

//	exit requires numeric argument
void	exit_numeric(t_tree *tree, t_env *ms_env, char c)
{
	(void)tree;
	ft_putstr_fd("exit\n", 2);
	if (c == 'z')
		ms_env->exitcode = 156;
	else if (c == 'd')
		ms_env->exitcode = 1;
	else if (c == 'e')
		ms_env->exitcode = 0;
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(tree->data[1], 2);
		ms_env->exitcode = 255;
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	(void)c;
	// ms_env->exitcode = 156;
	// if (c == 'a' || c == 'c')
	// {
	// 	ft_putstr_fd(": numeric argument required\n", 2);
	// 	ms_env->exitcode = 2;
	// }
	// else if (c == 'd')
	// 	ms_env->exitcode = 1;
	// else if (c == 'e')
	// 	ms_env->exitcode = 0;
	free_envi(ms_env, ms_env->exitcode);
}

//	check if exit has multiple arguments
void	exit_multi_arg(t_tree *tree, t_env *ms_env, int i)
{
	int	check;

	check = 0;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i > 2)
	{
		check = check_signs(tree->data[1]);
		if (check_isalpha(tree->data[1]) || check > 1)
			exit_numeric(tree, ms_env, 'b');
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			ms_env->exitcode = 1;
		}
	}
}

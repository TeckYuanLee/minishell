/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:28:31 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:28:31 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	check for child process's builtin
int	ft_check_builtin_child(t_tree *tree, t_env *ms_env)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tree->data[0], "echo", 4))
		i = ft_builtin_echo(ms_env, tree);
	else if (!ft_strncmp(tree->data[0], "cd", 3))
	{
		ms_env->exitcode = ms_cd(tree->data, ms_env);
		i++;
	}
	i = ft_check_builtin_add(tree, ms_env, i);
	if (!ft_strncmp(tree->data[0], "exit", 5))
	{
		ms_env->exitcode = ft_exit(tree, ms_env);
		i++;
	}
	if (i != 0)
		free_envi(ms_env, ms_env->exitcode);
	return (i);
}

//	print all env values retrieved by minishell
int	print_ms_env(char **argv, t_env *ms_env)
{
	t_item	*item;

	if (argv[1])
	{
		free_envi(ms_env, -100);
		ft_putstr_fd("minishell: env", 2);
		ft_putstr_fd(": argument(s) unsupported\n", 2);
		ft_putstr_fd("env: usage: env\n", 2);
		exit (1);
	}
	item = ms_env->item;
	while (item->key)
	{
		if (item->value)
			printf("%s=%s\n", item->key, item->value);
		item++;
	}
	return (0);
}

int	ft_check_builtin_add(t_tree *tree, t_env *ms_env, int i)
{
	if (!ft_strncmp(tree->data[0], "pwd", 4))
		i = ft_pwd_builtin(ms_env);
	else if (!ft_strncmp(tree->data[0], "export", 6))
	{
		ms_env->exitcode = ms_export(tree->data, ms_env);
		i++;
	}
	else if (!ft_strncmp(tree->data[0], "unset", 6))
	{
		ms_env->exitcode = ms_unset(tree->data, ms_env);
		i++;
	}
	else if (!ft_strncmp(tree->data[0], "env", 4))
	{
		ms_env->exitcode = print_ms_env(tree->data, ms_env);
		i++;
	}
	return (i);
}

//	check for builtin commands
int	ft_check_builtin(t_tree *tree, t_env *ms_env)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tree->data[0], "echo", 5))
		i = ft_builtin_echo(ms_env, tree);
	else if (!ft_strncmp(tree->data[0], "cd", 3) || \
		!ft_strncmp(tree->data[0], "exit", 5))
		free_envi(ms_env, 0);
	else if (!ft_strncmp(tree->data[0], "pwd", 4))
		i = ft_pwd_builtin(ms_env);
	if (!ft_strncmp(tree->data[0], "export", 7) && tree->data[1])
		free_envi(ms_env, 0);
	else if (!ft_strncmp(tree->data[0], "export", 7))
		free_envi(ms_env, ms_export(tree->data, ms_env));
	if (!ft_strncmp(tree->data[0], "unset", 6))
		i = 33;
	if (!ft_strncmp(tree->data[0], "env", 4))
	{
		ms_env->exitcode = print_ms_env(tree->data, ms_env);
		i++;
	}
	if (i != 0)
		free_envi(ms_env, ms_env->exitcode);
	printf("[check_builtin]%s\n", tree->data[1]);
	return (i);
}

//	check for export, cd, unset, exit
int	ft_start_builtin(t_tree *tree, t_env *ms_env, t_exec *exec)
{
	if (!ft_strncmp(tree->data[0], "export", 7) && tree->data[1])
	{
		ms_env->exitcode = ms_export(tree->data, ms_env);
		exec->builtin_check = 1;
	}
	else if (!ft_strncmp(tree->data[0], "cd", 3))
	{
		ms_env->exitcode = ms_cd(tree->data, ms_env);
		exec->builtin_check = 1;
	}
	else if (!ft_strncmp(tree->data[0], "unset", 6))
	{
		ms_env->exitcode = ms_unset(tree->data, ms_env);
		exec->builtin_check = 1;
	}
	else if (!ft_strncmp(tree->data[0], "exit", 5))
	{
		ms_env->exitcode = ft_exit(tree, ms_env);
		exec->builtin_check = 1;
	}
	return (0);
}

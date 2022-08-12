#include "minishell.h"

//	handle exit command
int	ft_exit(t_tree *tree, t_env *ms_env)
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
	ft_exit_multi_arg(tree, ms_env, i);
	ft_exit_one_arg(tree, ms_env, i);
	return (ms_env->exitcode);
}

//	exit if data is long long max, else if range greater long long max
void	ft_exit_one_range(t_tree *tree, t_env *ms_env)
{
	unsigned long long	range;

	range = ft_atoi_exit(tree->data[1]);
	if (!(ft_strcmp(tree->data[1], "9223372036854775807")))
	{
		ms_env->exitcode = (ft_atoi_exit(tree->data[1]) % 256);
		ft_putstr_fd("exit\n", 2);
		free_envi(ms_env, ms_env->exitcode);
	}
	else if (range > 9223372036854775806)
		ft_exit_numeric(tree, ms_env);
}

//	handle exit with only one argument
void	ft_exit_one_arg(t_tree *tree, t_env *ms_env, int i)
{
	int	check;

	check = 0;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i == 2)
	{
		check = ft_check_minus_plus(tree->data[1]);
		if (ft_check_isalpha(tree->data[1]) || check > 1)
			ft_exit_numeric(tree, ms_env);
		else if (!ft_check_isdigit(tree->data[1]) && check == 1)
			ft_exit_numeric(tree, ms_env);
		ft_exit_one_range(tree, ms_env);
		if (check == 1 && !(tree->data[1][0] == '+'))
		{
			check = (ft_atoi_exit(tree->data[1]) % 256);
			ms_env->exitcode = 256 - check;
			ft_putstr_fd("exit\n", 2);
			free_envi(ms_env, ms_env->exitcode);
		}
		else if (check == 0 || (tree->data[1][0] == '+'))
		{
			ms_env->exitcode = (ft_atoi_exit(tree->data[1]) % 256);
			ft_putstr_fd("exit\n", 2);
			free_envi(ms_env, ms_env->exitcode);
		}
	}
}

//	exit requires numeric argument
void	ft_exit_numeric(t_tree *tree, t_env *ms_env)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->data[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ms_env->exitcode = 255;
	free_envi(ms_env, ms_env->exitcode);
}

//	check if exit has multiple arguments
void	ft_exit_multi_arg(t_tree *tree, t_env *ms_env, int i)
{
	int	check;

	check = 0;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i > 2)
	{
		check = ft_check_minus_plus(tree->data[1]);
		if (ft_check_isalpha(tree->data[1]) || check > 1)
			ft_exit_numeric(tree, ms_env);
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: too many arguments\n", 2);
			ms_env->exitcode = 1;
		}
	}
}

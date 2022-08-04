#include "minishell.h"

//	handle exit command
int	ft_exit(t_tree *tree, t_env *envi, t_exec *exec)
{
	int	i;

	i = 0;
	while (tree->data[i])
		i++;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i == 1)
	{
		ft_putstr_fd("exit\n", 2);
		envi->exitcode = 0;
		ft_exit_free(tree, exec, envi);
		exit(envi->exitcode);
	}
	ft_exit_multi_arg(tree, envi, i, exec);
	ft_exit_one_arg(tree, envi, i, exec);
	return (envi->exitcode);
}

//	handle one argument exit with plus sign
void	ft_exit_one_arg_plus(t_tree *tree, t_env *envi, t_exec *exec)
{
	envi->exitcode = (ft_atoi_exit(tree->data[1]) % 256);
	ft_putstr_fd("exit\n", 2);
	ft_exit_free(tree, exec, envi);
	exit(envi->exitcode);
}

//	exit if data is long long max, else if range greater long long max
void	ft_exit_one_range(t_tree *tree, t_env *envi, t_exec *exec)
{
	unsigned long long	range;

	range = ft_atoi_exit(tree->data[1]);
	if (!(ft_strcmp(tree->data[1], "9223372036854775807")))
		ft_exit_one_arg_plus(tree, envi, exec);
	else if (range > 9223372036854775806)
		ft_exit_numeric(tree, envi, exec);
}

//	handle exit with only one argument
void	ft_exit_one_arg(t_tree *tree, t_env *envi, int i, t_exec *exec)
{
	int	check;

	check = 0;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i == 2)
	{
		check = ft_check_minus_plus(tree->data[1]);
		if (ft_check_isalpha(tree->data[1]) || check > 1)
			ft_exit_numeric(tree, envi, exec);
		else if (!ft_check_isdigit(tree->data[1]) && check == 1)
			ft_exit_numeric(tree, envi, exec);
		ft_exit_one_range(tree, envi, exec);
		if (check == 1 && !ft_isplus(tree->data[1]))
		{
			check = (ft_atoi_exit(tree->data[1]) % 256);
			envi->exitcode = 256 - check;
			ft_putstr_fd("exit\n", 2);
			ft_exit_free(tree, exec, envi);
			exit(envi->exitcode);
		}
		else if (check == 0 || ft_isplus(tree->data[1]))
			ft_exit_one_arg_plus(tree, envi, exec);
	}
}

//	exit requires numeric argument
void	ft_exit_numeric(t_tree *tree, t_env *envi, t_exec *exec)
{
	// ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->data[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	envi->exitcode = 255;
	ft_exit_free(tree, exec, envi);
	exit(envi->exitcode);
}

//	check if exit has multiple arguments
void	ft_exit_multi_arg(t_tree *tree, t_env *envi, int i, t_exec *exec)
{
	int	check;

	check = 0;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i > 2)
	{
		check = ft_check_minus_plus(tree->data[1]);
		if (ft_check_isalpha(tree->data[1]) || check > 1)
			ft_exit_numeric(tree, envi, exec);
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: too many arguments\n", 2);
			envi->exitcode = 1;
		}
	}
}

//	free envi
void	ft_exit_free(t_tree *tree, t_exec *exec, t_env *envi)
{
	(void)tree;
	(void)exec;
	free_envi(envi);
}

#include "minishell.h"

//	exit requires numeric argument
void	ft_exit_numeric(t_tree *tree, t_envi *envi, t_executor *exec)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(tree->data[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	envi->exitcode = 255;
	ft_exit_free(tree, exec, envi);
	exit(envi->exitcode);
}

//	check for alphabets or single quotes
int	ft_check_isalpha(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]) || str[i] == 39)
			return (1);
	return (0);
}

//	check for + and - signs
int	ft_check_minus_plus(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] == '-')
			check++;
		if (str[i] == '+')
			check++;
		i++;
	}
	return (check);
}

//	check if exit has multiple arguments
void	ft_exit_multi_arg(t_tree *tree, t_envi *envi, int i, t_executor *exec)
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
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			envi->exitcode = 1;
		}
	}
}

//	free envi
void	ft_exit_free(t_tree *tree, t_executor *exec, t_envi *envi)
{
	(void)tree;
	(void)exec;
	free_envi(envi);
}

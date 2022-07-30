#include "minishell.h"

//	skip whitespaces
static int	ft_skip(const char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
			str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
	{
		i++;
	}
	return (i);
}

//	handle one argument exit with plus sign
void	ft_exit_one_arg_plus(t_tree *tree, t_envi *envi, t_executor *exec)
{
	envi->exitcode = (ft_atoi_exit(tree->data[1]) % 256);
	ft_putstr_fd("exit\n", 2);
	ft_exit_free(tree, exec, envi);
	exit(envi->exitcode);
}

//	long long atoi for exit command
long long	ft_atoi_exit(const char *str)
{
	long long	value;
	long long	i;
	long long	sign;

	i = ft_skip(str, 0);
	value = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}

//	check for + sign
int	ft_isplus(char *str)
{
	if (str[0] == '+')
		return (1);
	return (0);
}

//	exit if data is long long max, else if range greater long long max
void	ft_exit_one_range(t_tree *tree, t_envi *envi, t_executor *exec)
{
	unsigned long long	range;

	range = ft_atoi_exit(tree->data[1]);
	if (!(ft_strcmp(tree->data[1], "9223372036854775807")))
		ft_exit_one_arg_plus(tree, envi, exec);
	else if (range > 9223372036854775806)
		ft_exit_numeric(tree, envi, exec);
}

//	check for digits within the string
int	ft_check_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isdigit(str[i]))
			return (1);
	return (0);
}

//	handle exit with only one argument
void	ft_exit_one_arg(t_tree *tree, t_envi *envi, int i, t_executor *exec)
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

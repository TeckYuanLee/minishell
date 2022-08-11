#include "minishell.h"

//	size_t atoi for exit command
size_t	ft_atoi_exit(const char *str)
{
	size_t	value;
	size_t	i;
	size_t	sign;

	i = 0;
	value = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		value = (value * 10) + (str[i++] - '0');
	return (value * sign);
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

	i = -1;
	check = 0;
	while (str[++i])
	{
		if (str[i] == '-')
			check++;
		if (str[i] == '+')
			check++;
	}
	return (check);
}

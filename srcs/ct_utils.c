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

//	check for + sign
int	ft_isplus(char *str)
{
	if (str[0] == '+')
		return (1);
	return (0);
}

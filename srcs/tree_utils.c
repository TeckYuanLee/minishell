/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:33:00 by telee             #+#    #+#             */
/*   Updated: 2022/08/19 10:59:15 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	size_t atoi for exit command
size_t	atoi_exit(const char *str)
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
int	check_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isdigit(str[i]))
			return (1);
	return (0);
}

//	check for alphabets or single quotes
int	check_isalpha(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]) || str[i] == 39)
			return (1);
	return (0);
}

//	check for + and - signs
int	check_signs(char *str)
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
